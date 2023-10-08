//
// for Lex File Analysis by line
//
#include "sly/AttrDict.h"
#include "sly/FaModel.h"
#include "sly/LrParser.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include "sly/Token.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <sly/sly.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using sly::core::type::AttrDict;
using sly::core::type::Production;
using sly::core::type::Token;
using sly::core::lexical::RegEx;
using sly::runtime::Stream2TokenPipe;
using sly::core::grammar::LrParser;
using sly::utils::replace_all;
using namespace std;


/**
 * .l file analysis: 
 * 
 * delim  %%[\r\n]
 * lbrace   %{[\r\n]
 * rbrace   %}[\r\n]
 * line     .*[\r\n]
 * 
 * LexFile <- Defs delim Rules delim Sub eof
 * Defs <- DefsLine Defs | lbrace Codes rbrace | 
 * Codes <- CodesLine Codes | 
 * CodesLine <- line {}
 * DefsLine <- line {word blank RegEx "\n"}
 * Rules <- RulesLine Rules | 
 * RulesLine <- line {LexRegEx blank CodePart "\n"}
 * Sub <- SubLine Sub | 
 * SubLine <- line {}
 **/

/**
 * .y file analysis: 
 * 
 * delim       %%[\r\n]
 * line        .*[\r\n]
 * 
 * YaccFile <-  Defs delim ProdLines delim Sub eof
 * Defs <- DefsLine Defs | 
 * ProdLines <- ProdLine ProdLines | 
 * Sub <- SubLine Sub | 
 * SubLine <- line {}
 **/

struct LexParms {
  struct LexDef {
    string name;
    string regex;
  };
  struct LexRule {
    string exp;
    string code;
  };

  // lexDef = {{name: "D", regex: "[0-9]"}, {name: "L", regex: "[a-zA-Z]"}, ...}
  vector<LexDef> lexDefs;
  // lexRule = {{exp: "0[0-7]*{IS}?", code: "{ count(); retur(CONSTANT) }"}, ...}
  vector<LexRule>  lexRules;
  // headCodeblock = "#include <stdio.h>\n#include "y.tab.h"\n..."
  string headCodeblock;
  // tailCodeblock = "int yywrap(void)\n{\n        return 1;\n}\n..."
  string tailCodeblock;

  void Print(ostream &oss) const;
};

struct YaccParms {
  struct YaccProd {
    string startToken;
    vector<string> nextTokens;
  };

  // yaccStartToken = "translation_unit"
  string yaccStartToken;
  // yaccTokens = {"IDENTIFIER", "CONSTANT", "SIZEOF", ...}
  vector<string> yaccTokens;
  // yaccProds = {{startToken: "and_expression", nextTokens: {"and_expression" "'&'", "equality_expression"}}}
  vector<YaccProd> yaccProds;
  // tailCodeblock = "#include <stdio.h>\n\nextern char yytext[]\n...";
  string tailCodeblock;

  void Print(ostream &oss) const;
};

struct Parms {
  struct lexToken {
    string regex;
    string action;
  };
  struct Prod {
    string startToken;
    vector<string> nextTokens;
  };
  vector<lexToken> lexTokens;
  string startToken;
  set<string> terminalTokens;
  set<string> nonTerminalTokens;
  vector<Prod> prods;

  void Print(ostream &oss) const;
};

Parms ParseParameters(LexParms lexParms, YaccParms yaccParms) {
  Parms parms;
  auto lexRegex2regex = [](const string &exp) -> string {
    // headache, fuck lex regex
    // L?\"(\\.|[^\\"\n])*\"
    stringstream ss;
    bool isEscape = false;
    bool isLiteral = false;
    for (char c : exp) {
      if (isEscape) {
        if (c == '"') {
          ss << c;
        } else {
          ss << '\\' << c;
        }
        isEscape = false;
      } else if (c == '\\') {
        isEscape = true;
      } else if (c == '"') {
        ss << (isLiteral ? ")" : "(");
        isLiteral = !isLiteral;
      } else {
        if (isLiteral && (c == '(' || c == ')' || c == '[' || 
            c == ']' || c == '^' || c == '*' || c == '.' ||
            c == '+' || c == '|')) {
          ss << '\\' << c;
        } else {
          ss << c;
        }
      }
    }
    return ss.str();
  };
  // initialize lexTokens
  for (auto rule : lexParms.lexRules) {
    // transform lex-regex to regex
    rule.exp = lexRegex2regex(rule.exp);
    // replace {D} with its regex
    // inversely visit, to supoort recursive call
    for (auto it = lexParms.lexDefs.rbegin(); it != lexParms.lexDefs.rend(); it++) {
      auto &name = it->name;
      auto &regex = it->regex;
      replace_all(rule.exp, "{" + name + "}", regex);
    }
    parms.lexTokens.push_back({rule.exp, rule.code});
  }

  parms.startToken = yaccParms.yaccStartToken;
  // initialize terminalTokens, nonTerminalTokens
  parms.terminalTokens.insert(yaccParms.yaccStartToken);
  for (const string &tokenName : yaccParms.yaccTokens) {
    parms.terminalTokens.insert(tokenName);
  }
  for (const auto &[startToken, nextTokens] : yaccParms.yaccProds) {
    parms.terminalTokens.erase(startToken);
    parms.nonTerminalTokens.insert(startToken);
  }

  /// initialize prods
  for (const auto &[startToken, nextTokens] : yaccParms.yaccProds) {
    parms.prods.push_back({startToken, nextTokens});
  }

  return parms;
}

void LexParms::Print(ostream &oss) const{
    oss << "Defs: " << endl;
    for (const auto &lexDef : lexDefs) {
      oss << "  " << lexDef.name << ": " << lexDef.regex << endl;
    }
    oss << "Rules: " << endl;
    for (const auto &lexRule : lexRules) {
      oss << "  " << lexRule.exp << ": " << endl;
      oss << "    " << lexRule.code << endl;
    }
    oss << "Head Codeblock: " << endl;
    oss << headCodeblock << endl;
    oss << "Tail Codeblock: " << endl;
    oss << tailCodeblock << endl;
  }

void YaccParms::Print(ostream &oss) const{
    oss << "Tokens: " << endl;
    for (const auto &token : yaccTokens) {
      oss << "  " << token << endl;
    }
    oss << "Start Token: " << endl;
    oss << "  " << yaccStartToken << endl;
    oss << "Production: "<< endl;
    for (const auto &prod : yaccProds) {
      oss << "  " << prod.startToken << ": " << endl;
      oss << "    ";
      for (const auto &nextToken : prod.nextTokens) {
        oss << nextToken << " ";
      }
      oss << endl;
    }
    oss << "Tail Codeblock: " << endl;
    oss << tailCodeblock << endl;
  }

void Parms::Print(ostream &oss) const {
  oss << "Lex Tokens: " << endl;
  for (const auto &[regex, action] : lexTokens) {
    oss << "  " << regex << ": " << endl;
    oss << "    " << action << endl;
  }
  oss << "Token Terminators: " << endl;
  for (const auto &token : terminalTokens) {
    oss << "  " << token << endl;
  }
  oss << "Token NonTerminators: " << endl;
  for (const auto &token : nonTerminalTokens) {
    oss << "  " << token << endl;
  }
  oss << "Start Token: " << endl;
    oss << "  " << startToken << endl;
  oss << "Productions: " << endl;
  for (const auto &[start, nexts] : prods) {
    oss << "  " << start << ": " << endl;
    oss << "    ";
    for (const auto &next : nexts) {
      oss << next << " ";
    }
    oss << endl;
  }
}

LexParms ParseLexParameters(stringstream &file_stream) {
  LexParms lexParms;
  const auto ending = Token::Terminator("EOF_FLAG");

  static optional<Stream2TokenPipe> s2ppl;
  static optional<LrParser> parser;
  // initialize s2ppl and parser
  if (!s2ppl.has_value() || !parser.has_value()) {
    auto delim  = Token::Terminator("delim");
    auto lbrace = Token::Terminator("lbrace");
    auto rbrace = Token::Terminator("rbrace");
    auto line   = Token::Terminator("line");
    // auto ending = Token::Terminator("EOF_FLAG");
    RegEx re_delim  {R"(%%[\r\n]+)"};
    RegEx re_lbrace {R"(%{[\r\n]+)"};
    RegEx re_rbrace {R"(%}[\r\n]+)"};
    RegEx re_line   {R"([^\r\n]*[\r\n]+)"};
    auto LexFile   = Token::NonTerminator("LexFile");
    auto Defs      = Token::NonTerminator("Defs");
    auto DefsLine  = Token::NonTerminator("DefsLine");
    auto Rules     = Token::NonTerminator("Rules");
    auto RulesLine = Token::NonTerminator("RulesLine");
    auto Sub       = Token::NonTerminator("Sub");
    auto SubLine   = Token::NonTerminator("SubLine");
    auto Codes     = Token::NonTerminator("Codes");
    auto CodesLine = Token::NonTerminator("CodesLine");
    vector<Production> productions = {
        // LexFile <- Defs delim Rules delim Sub
        Production(LexFile, {[](vector<YYSTATE> &v) {
          }})(Defs)(delim)(Rules)(delim)(Sub),
        // Defs <- DefsLine Defs
        Production(Defs, {[](vector<YYSTATE> &v) {
          }})(DefsLine)(Defs),
        // Defs <- lbrace Codes rbrace | 
        Production(Defs, {[](vector<YYSTATE> &v) {
          }})(lbrace)(Codes)(rbrace),
        // Defs <- 
        Production(Defs, {[](vector<YYSTATE> &v) {
          }}),
        // Codes <- CodesLine Codes | 
        Production(Codes, {[](vector<YYSTATE> &v) {
          }})(CodesLine)(Codes),
        // Codes <- CodesLine Codes | 
        Production(Codes, {[](vector<YYSTATE> &v) {
          }}),
        // CodesLine <- line {}
        Production(CodesLine, {[&lexParms](vector<YYSTATE> &v) {
            // CodesLine: copy code
            // TODO
            lexParms.headCodeblock += v[1].Get<string>("lval");
          }})(line),
        // DefsLine <- line
        Production(DefsLine, {[&lexParms](vector<YYSTATE> &v) {
            // DefsLine: word blank RegEx
            // TODO
            const string &str = v[1].Get<string>("lval");
            size_t pos = str.find_first_of(" \t\n\r\0");
            string defName = str.substr(0, pos);
            string defRegex = str.substr(pos + 1);
            sly::utils::trim(defName, " \t\n\r\0");
            sly::utils::trim(defRegex, " \t\n\r\0");
            lexParms.lexDefs.push_back({defName, defRegex});
          }})(line),
        // Rules <- RulesLine Rules
        Production(Rules, {[](vector<YYSTATE> &v) {
          }})(RulesLine)(Rules),
        // Rules <- 
        Production(Rules, {[](vector<YYSTATE> &v) {
          }}),
        // RulesLine <- line
        Production(RulesLine, {[&lexParms](vector<YYSTATE> &v) {
            // RulesLine: LexRegEx blank CodePart
            // TODO
            const string &str = v[1].Get<string>("lval");
            size_t pos = min(str.find(" {"), str.find("\t{"));
            string lexRegEx = str.substr(0, pos);
            string codePart = str.substr(pos + 1);
            sly::utils::trim(lexRegEx, " \t\n\r\0");
            sly::utils::trim(codePart, " \t\n\r\0");
            lexParms.lexRules.push_back({lexRegEx, codePart});
          }})(line),
        // Sub <- SubLine Sub
        Production(Sub, {[](vector<YYSTATE> &v) {
          }})(SubLine)(Sub),
         // Sub <- 
        Production(Sub, {[](vector<YYSTATE> &v) {
          }}),
        // SubLine <- line {}
        Production(SubLine, {[&lexParms](vector<YYSTATE> &v) {
            // Subline: copy code
            // TODO
            lexParms.tailCodeblock += v[1].Get<string>("lval");
          }})(line),
    };
    sly::core::grammar::ContextFreeGrammar cfg(productions, LexFile, ending);
    sly::core::grammar::Lr1 lr1;
    cfg.Compile(lr1);
    auto table = cfg.GetLrTable();
    table.Print(cout);
    parser = LrParser(table);
    // define transition and state
    auto [transition, state] = sly::core::lexical::DfaModel::Merge({
        re_delim.GetDfaModel(),
        re_lbrace.GetDfaModel(),
        re_rbrace.GetDfaModel(),
        re_line.GetDfaModel(),
    });
    s2ppl = sly::runtime::Stream2TokenPipe(transition, state, {
        delim, lbrace, rbrace, line, 
    }, ending);
  }

  // parse
  vector<AttrDict> attributes;
  vector<Token> tokens;
  file_stream << "\r\n";
  while (true) {
    auto token = s2ppl.value().Defer(file_stream);
    AttrDict ad;
    ad.Set("lval", s2ppl.value().buffer_); 

    tokens.emplace_back(token);
    attributes.emplace_back(ad);
    if (token == ending)
      break;
  }
  parser.value().Parse(tokens, attributes);
  auto tree = parser.value().GetTree();
  tree.Annotate();
  
  // cout << "\n\nAfter Annotate:" << endl;
  // tree.Print(std::cout);
  // cout << "\n\nThe Expr: " << input_string << endl;

  // cout << "Lex Parameters:" << endl;
  // lexParms.Print(std::cout);

  return lexParms;
}

YaccParms ParseYaccParameters(stringstream &file_stream) {
  YaccParms yaccParms;
  const auto ending = Token::Terminator("EOF_FLAG");

  static optional<Stream2TokenPipe> s2ppl;
  static optional<LrParser> parser;
  // initialize s2ppl and parser
  if (!s2ppl.has_value() || !parser.has_value()) {
    // initialize s2ppl
    auto delim  = Token::Terminator("delim");
    auto line   = Token::Terminator("line");
    // auto ending = Token::Terminator("EOF_FLAG");
    RegEx re_delim {R"(%%[\r\n]+)"};
    RegEx re_line  {R"([^\r\n]*[\r\n]+)"};
    auto YaccFile  = Token::NonTerminator("YaccFile");
    auto Defs      = Token::NonTerminator("Defs");
    auto DefsLine  = Token::NonTerminator("DefsLine");
    auto Prods     = Token::NonTerminator("Prods");
    auto ProdLine  = Token::NonTerminator("ProdLine");
    auto Sub       = Token::NonTerminator("Sub");
    auto SubLine   = Token::NonTerminator("SubLine");
    vector<Production> productions = {
        // YaccFile <- Defs delim Prods delim Sub
        Production(YaccFile, {[&yaccParms](vector<YYSTATE> &v) {
            // parse Productions
            {
              stringstream ss;
              ss.str(v[3].Get<string>("lval"));

              int state = 0;
              string startToken;
              vector<string> nextTokens;

              string str;
              while (!ss.eof()) {
                ss >> str;
                if (str.length() == 0) {
                  break;
                }
                switch (state) {
                  case 0:
                    startToken = str;
                    state = 1;
                    break;
                  case 1:
                    assert(str == ":");
                    state = 2;
                    break;
                  case 2:
                    if (str == "|") {
                      yaccParms.yaccProds.push_back({startToken, nextTokens});
                      nextTokens.resize(0);
                      state = 2;
                    } else if (str == ";") {
                      yaccParms.yaccProds.push_back({startToken, nextTokens});
                      nextTokens.resize(0);
                      state = 0;
                    } else {
                      nextTokens.emplace_back(str);
                      state = 2;
                    }
                    break;
                }
              }
            }
          }})(Defs)(delim)(Prods)(delim)(Sub),
        // Defs <- DefsLine Defs
        Production(Defs, {[](vector<YYSTATE> &v) {
          }})(DefsLine)(Defs),
        // Defs <- 
        Production(Defs, {[](vector<YYSTATE> &v) {
          }}),
        // DefsLine <- line
        Production(DefsLine, {[&yaccParms](vector<YYSTATE> &v) {
            // parse symbol definitions
            // DefsLine: %token word word word ... / %start word
            const string &str = v[1].Get<string>("lval");
            stringstream ss;
            ss.str(str);

            string word;
            ss >> word;
            if (word == "%token") {
              while (true) {
                ss >> word;
                if (word.length() == 0 || ss.eof()) {
                  break;
                }
                yaccParms.yaccTokens.emplace_back(word);
              }
            } else if (word == "%start") {
              ss >> word;
              yaccParms.yaccStartToken = word;
            }
          }})(line),
        // Prods <- ProdLine Prods
        Production(Prods, {[](vector<YYSTATE> &v) {
            string str = v[1].Get<string>("lval");
            str += v[2].Get<string>("lval");
            v[0].Set<string>("lval", str);
          }})(ProdLine)(Prods),
        // Prods <- 
        Production(Prods, {[](vector<YYSTATE> &v) {
          v[0].Set<string>("lval", "");
          }}),
        // ProdLine <- line
        Production(ProdLine, {[&yaccParms](vector<YYSTATE> &v) {
            v[0].Set<string>("lval", v[1].Get<string>("lval"));
          }})(line),
        // Sub <- SubLine Sub
        Production(Sub, {[](vector<YYSTATE> &v) {
          }})(SubLine)(Sub),
         // Sub <- 
        Production(Sub, {[](vector<YYSTATE> &v) {
          }}),
        // SubLine <- line {}
        Production(SubLine, {[&yaccParms](vector<YYSTATE> &v) {
            // Subline: copy code
            // TODO
            yaccParms.tailCodeblock += v[1].Get<string>("lval");
          }})(line),
    };
    sly::core::grammar::ContextFreeGrammar cfg(productions, YaccFile, ending);
    sly::core::grammar::Lr1 lr1;
    cfg.Compile(lr1);
    auto table = cfg.GetLrTable();
    parser = LrParser(table);

    // 定义词法 transition 和 state
    auto [transition, state] = sly::core::lexical::DfaModel::Merge({
        re_delim.GetDfaModel(),
        re_line.GetDfaModel(),
    });
    s2ppl = sly::runtime::Stream2TokenPipe(transition, state, {
        delim, line, 
    }, ending);
  }

  // parse
  vector<AttrDict> attributes;
  vector<Token> tokens;
  file_stream << "\r\n";
  while (true) {
    auto token = s2ppl.value().Defer(file_stream);
    AttrDict ad;
    ad.Set("lval", s2ppl.value().buffer_); 
    tokens.emplace_back(token);
    attributes.emplace_back(ad);
    if (token == ending)
      break;
  }
  parser.value().Parse(tokens, attributes);
  auto tree = parser.value().GetTree();
  tree.Annotate();

  // cout << "\n\nAfter Annotate:" << endl;
  // tree.Print(std::cout);

  // cout << "Yacc Parameters:" << endl;
  // yaccParms.Print(std::cout);

  return yaccParms;
}

inline std::string regex2code(const std::string &str) {
  std::string res = str;
  replace_all(res, "+", "\\+");
  replace_all(res, "*", "\\*");
  replace_all(res, "", "\\n");
  return res;
}

void generateCodeFile(Parms parms, ostream &oss) {
  /* section 1 */
  oss << R"(/* section 1 */)" << endl;
  oss << R"(#include "sly/AttrDict.h")" << endl;
  oss << R"(#include "sly/FaModel.h")" << endl;
  oss << R"(#include "sly/LrParser.h")" << endl;
  oss << R"(#include "sly/RegEx.h")" << endl;
  oss << R"(#include "sly/Stream2TokenPipe.h")" << endl;
  oss << R"(#include <sly/sly.h>)" << endl;
  oss << R"()" << endl;
  oss << R"(#include <iostream>)" << endl;
  oss << R"(#include <fstream>)" << endl;
  oss << R"(#include <sstream>)" << endl;
  oss << R"(#include <vector>)" << endl;
  oss << R"()" << endl;
  oss << R"(using sly::core::type::AttrDict;)" << endl;
  oss << R"(using sly::core::type::Production;)" << endl;
  oss << R"(using sly::core::type::Token;)" << endl;
  oss << R"(using sly::core::lexical::RegEx;)" << endl;
  oss << R"(using sly::core::lexical::DfaModel;)" << endl;
  oss << R"(using sly::runtime::Stream2TokenPipe;)" << endl;
  oss << R"(using sly::core::grammar::LrParser;)" << endl;
  oss << R"(using namespace std;)" << endl;
  oss << endl;

  /* section 2 */
  int num_lexical_tokens = parms.lexTokens.size();
  int num_syntax_tokens = parms.terminalTokens.size() + parms.nonTerminalTokens.size();
  oss << "/* section 2 */" << endl;
  oss << "//@variable" << endl;
  oss << "const int num_lexical_tokens = " << num_lexical_tokens << ";" << endl;
  oss << "const int num_syntax_tokens = " << num_syntax_tokens << ";" << endl;
  oss << endl;
  oss << "auto ending = Token::Terminator(\"EOF_FLAG\");" << endl;
  oss << endl;
  oss << "//@variable" << endl;
  int tokenIdx = 256;
  for (const string &tokenName : parms.terminalTokens) {
    oss << "#define " << tokenName << " " << tokenIdx++ << endl;
  }
  for (const string &tokenName : parms.nonTerminalTokens) {
    oss << "#define " << tokenName << " " << tokenIdx++ << endl;
  }
  oss << endl;

  /* section 3 */
  oss << "/* section 3 */" << endl;
  oss << "// syntax tokens " << endl;
  oss << "Token syntax_tokens[256 + num_syntax_tokens] = {" << endl;
  for (tokenIdx = 0; tokenIdx <= 255; tokenIdx++) {
    oss << "  Token::Terminator(string(1, " << tokenIdx << ")), " << endl;
  }
  for (const string &tokenName : parms.terminalTokens) {
    oss << "  Token::Terminator(\"" << tokenName << "\"), // " << tokenIdx++ << endl;
  }
  for (const string &tokenName : parms.nonTerminalTokens) {
    oss << "  Token::NonTerminator(\"" << tokenName << "\"), // " << tokenIdx++ << endl;
  }
  oss << "};" << endl;
  oss << endl;
  oss << "//@variable" << endl;
  oss << "auto &start_syntax_token = syntax_tokens[" << parms.startToken << "];" << endl;
  oss << endl;

  /* section 4 */
  oss << "/* section 4 */" << endl;
  oss << "//@variable" << endl;
  oss << "vector<Production> productions = {" << endl;
  for (const auto &prod : parms.prods) {
    oss << "  // " << prod.startToken << " : ";
    for (const string &nextToken : prod.nextTokens) {
      oss << nextToken << " ";
    }
    oss << ";" << endl;
    oss << "  Production(syntax_tokens[" << prod.startToken << "], {[](vector<YYSTATE> &v) {" << endl;
    oss << "      // action ..." << endl;
    oss << "    }})";
    for (const string &nextToken : prod.nextTokens) {
      oss << "(syntax_tokens[" << nextToken << "])";
    }
    oss << ", " << endl;
  }
  oss << "};" << endl;

  /* section 5 */
  oss << R"(/* section 5 */)" << endl;
  oss << R"(void count() {)" << endl;
  oss << R"(  // pass)" << endl;
  oss << R"(})" << endl;
  oss << R"()" << endl;
  oss << R"(void comment() {)" << endl;
  oss << R"(  // pass)" << endl;
  oss << R"(})" << endl;
  oss << R"()" << endl;
  oss << R"(int check_type(void))" << endl;
  oss << R"({)" << endl;
  oss << R"(  return IDENTIFIER;)" << endl;
  oss << R"(})" << endl;

  oss << endl;
  oss << endl;

  /* section 6 */
  oss << "/* section 6 */" << endl;
  oss << "//@variable" << endl;
  oss << "IdType to_syntax_token_id(Token lexical_token, AttrDict &ad) {" << endl;
  oss << "  string token_name = lexical_token.GetTokName();" << endl;
  oss << "  ";
  for (const auto &[regex, action] : parms.lexTokens) {
    oss << "if (token_name == R\"(" << regex << ")\") { " << endl;
    oss << "    { " << action << "}" << endl;
    oss << "  } else ";
  }
  oss << " {" << endl;
  oss << "    return 0;" << endl;
  oss << "  }" << endl;
  oss << "  return 0;" << endl;
  oss << "}" << endl;
  oss << endl;

  /* section 7 */
  oss << "/* section 7 */" << endl;
  oss << "int main() {" << endl;

  /* section 7.1 */
  oss << "  /* section 7.1 */" << endl;
  oss << "  spdlog::set_level(spdlog::level::info);" << endl;
  oss << "  " << endl;
  
  /* section 7.2 */
  oss << "  /* section 7.2 */" << endl;
  oss << "  // lexical token" << endl;
  oss << "  //@variable" << endl;
  oss << "  vector<Token> lexical_tokens = {" << endl;
  for (const auto &[regex, action] : parms.lexTokens) {
    oss << "    Token::Terminator(R\"(" << regex << ")\"), "<< endl;
  }
  oss << "  };" << endl;
  oss << "  vector<RegEx> lexical_tokens_regex = {" << endl;
  for (const auto &[regex, action] : parms.lexTokens) {
    oss << "    RegEx(R\"(" << regex << ")\"), "<< endl;
  }
  oss << "  };" << endl;

  /* section 7.3 */
  oss << R"(
  /* section 7.3 */
  vector<DfaModel> lexical_tokens_dfa;
  for (auto regex : lexical_tokens_regex) {
    lexical_tokens_dfa.push_back(regex.GetDfaModel());
  }
  auto [transition, state] = sly::core::lexical::DfaModel::Merge(lexical_tokens_dfa);
  auto s2ppl = Stream2TokenPipe(transition, state, lexical_tokens, ending);

  // syntax
  sly::core::grammar::ContextFreeGrammar cfg(productions, start_syntax_token, ending);
  sly::core::grammar::Lr1 lr1;
  cfg.Compile(lr1);
  auto table = cfg.GetLrTable();
  LrParser parser(table);

  cout << start_syntax_token.GetTokName() << endl;)";
  oss << endl;

  /* section 7.4 */
  oss << R"(
  /* section 7.4 */
  // runtime
  stringstream input_stream;
  {
    ifstream inputFile("../demo/1.in");
    input_stream << inputFile.rdbuf();
    inputFile.close();
  }

  vector<AttrDict> attributes;
  vector<Token> tokens;
  while (true) {
    auto lexical_token = s2ppl.Defer(input_stream);
    if (lexical_token == ending)
      break;
    AttrDict ad;
    ad.Set("lval", s2ppl.buffer_); 

    IdType id = to_syntax_token_id(lexical_token, ad);
    if (id == 0) 
      continue;
    Token syntax_token = syntax_tokens[id];

    tokens.emplace_back(syntax_token);
    attributes.emplace_back(ad);
  }

  cerr << "tokens: " << endl;
  for (int i = 0; i < tokens.size(); i++) {
    auto token = tokens[i];
    auto ad = attributes[i];
    cerr << "  " << ad.Get<string>("lval") << " : " << token.GetTokName() << endl;
  }

  parser.Parse(tokens, attributes);
  auto tree = parser.GetTree();
  cerr << "parse tree: " << endl;
  tree.Print(std::cerr);

  return 0;)";
  oss << endl;

  oss << "}" << endl;
}

int main() {
  // ignore warnings
  spdlog::set_level(spdlog::level::warn);

  stringstream lex_file_stream;
  stringstream yacc_file_stream;
  {
    ifstream lexFile("../demo/1.l");
    lex_file_stream << lexFile.rdbuf();
    lexFile.close();

    ifstream yaccFile("../demo/1.y");
    yacc_file_stream << yaccFile.rdbuf();
    yaccFile.close();
  }

  auto lexParms = ParseLexParameters(lex_file_stream);
  // lexParms.Print(std::cout);
  auto yaccParms = ParseYaccParameters(yacc_file_stream);
  // yaccParms.Print(std::cout);
  auto parms = ParseParameters(lexParms, yaccParms);
  parms.Print(std::cout);

  ofstream output_file_stream("../test/out.cpp");
  generateCodeFile(parms, output_file_stream);
  Token::Terminator("A\trigid\t\\123\\token").PrintImpl(cout);
  cout << endl;
  return 0;
}
