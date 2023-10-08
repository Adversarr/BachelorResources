/* section 1 */
#include "sly/AttrDict.h"
#include "sly/FaModel.h"
#include "sly/LrParser.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include <sly/sly.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using sly::core::type::AttrDict;
using sly::core::type::Production;
using sly::core::type::Token;
using sly::core::lexical::RegEx;
using sly::core::lexical::DfaModel;
using sly::runtime::Stream2TokenPipe;
using sly::core::grammar::LrParser;
using namespace std;

/* section 2 */
//@variable
const int num_lexical_tokens = 18;
const int num_syntax_tokens = 17;

auto ending = Token::Terminator("EOF_FLAG");

//@variable
#define CONSTANT 256
#define IDENTIFIER 257
#define IF 258
#define INT 259
#define RETURN 260
#define STRING_LITERAL 261
#define assignment_expression 262
#define block_item 263
#define block_item_list 264
#define compound_statement 265
#define declaration 266
#define declaration_specifiers 267
#define external_declaration 268
#define function_definition 269
#define init_declarator 270
#define init_declarator_list 271
#define translation_unit 272

/* section 3 */
// syntax tokens 
Token syntax_tokens[256 + num_syntax_tokens] = {
  Token::Terminator(string(1, 0)), 
  Token::Terminator(string(1, 1)), 
  Token::Terminator(string(1, 2)), 
  Token::Terminator(string(1, 3)), 
  Token::Terminator(string(1, 4)), 
  Token::Terminator(string(1, 5)), 
  Token::Terminator(string(1, 6)), 
  Token::Terminator(string(1, 7)), 
  Token::Terminator(string(1, 8)), 
  Token::Terminator(string(1, 9)), 
  Token::Terminator(string(1, 10)), 
  Token::Terminator(string(1, 11)), 
  Token::Terminator(string(1, 12)), 
  Token::Terminator(string(1, 13)), 
  Token::Terminator(string(1, 14)), 
  Token::Terminator(string(1, 15)), 
  Token::Terminator(string(1, 16)), 
  Token::Terminator(string(1, 17)), 
  Token::Terminator(string(1, 18)), 
  Token::Terminator(string(1, 19)), 
  Token::Terminator(string(1, 20)), 
  Token::Terminator(string(1, 21)), 
  Token::Terminator(string(1, 22)), 
  Token::Terminator(string(1, 23)), 
  Token::Terminator(string(1, 24)), 
  Token::Terminator(string(1, 25)), 
  Token::Terminator(string(1, 26)), 
  Token::Terminator(string(1, 27)), 
  Token::Terminator(string(1, 28)), 
  Token::Terminator(string(1, 29)), 
  Token::Terminator(string(1, 30)), 
  Token::Terminator(string(1, 31)), 
  Token::Terminator(string(1, 32)), 
  Token::Terminator(string(1, 33)), 
  Token::Terminator(string(1, 34)), 
  Token::Terminator(string(1, 35)), 
  Token::Terminator(string(1, 36)), 
  Token::Terminator(string(1, 37)), 
  Token::Terminator(string(1, 38)), 
  Token::Terminator(string(1, 39)), 
  Token::Terminator(string(1, 40)), 
  Token::Terminator(string(1, 41)), 
  Token::Terminator(string(1, 42)), 
  Token::Terminator(string(1, 43)), 
  Token::Terminator(string(1, 44)), 
  Token::Terminator(string(1, 45)), 
  Token::Terminator(string(1, 46)), 
  Token::Terminator(string(1, 47)), 
  Token::Terminator(string(1, 48)), 
  Token::Terminator(string(1, 49)), 
  Token::Terminator(string(1, 50)), 
  Token::Terminator(string(1, 51)), 
  Token::Terminator(string(1, 52)), 
  Token::Terminator(string(1, 53)), 
  Token::Terminator(string(1, 54)), 
  Token::Terminator(string(1, 55)), 
  Token::Terminator(string(1, 56)), 
  Token::Terminator(string(1, 57)), 
  Token::Terminator(string(1, 58)), 
  Token::Terminator(string(1, 59)), 
  Token::Terminator(string(1, 60)), 
  Token::Terminator(string(1, 61)), 
  Token::Terminator(string(1, 62)), 
  Token::Terminator(string(1, 63)), 
  Token::Terminator(string(1, 64)), 
  Token::Terminator(string(1, 65)), 
  Token::Terminator(string(1, 66)), 
  Token::Terminator(string(1, 67)), 
  Token::Terminator(string(1, 68)), 
  Token::Terminator(string(1, 69)), 
  Token::Terminator(string(1, 70)), 
  Token::Terminator(string(1, 71)), 
  Token::Terminator(string(1, 72)), 
  Token::Terminator(string(1, 73)), 
  Token::Terminator(string(1, 74)), 
  Token::Terminator(string(1, 75)), 
  Token::Terminator(string(1, 76)), 
  Token::Terminator(string(1, 77)), 
  Token::Terminator(string(1, 78)), 
  Token::Terminator(string(1, 79)), 
  Token::Terminator(string(1, 80)), 
  Token::Terminator(string(1, 81)), 
  Token::Terminator(string(1, 82)), 
  Token::Terminator(string(1, 83)), 
  Token::Terminator(string(1, 84)), 
  Token::Terminator(string(1, 85)), 
  Token::Terminator(string(1, 86)), 
  Token::Terminator(string(1, 87)), 
  Token::Terminator(string(1, 88)), 
  Token::Terminator(string(1, 89)), 
  Token::Terminator(string(1, 90)), 
  Token::Terminator(string(1, 91)), 
  Token::Terminator(string(1, 92)), 
  Token::Terminator(string(1, 93)), 
  Token::Terminator(string(1, 94)), 
  Token::Terminator(string(1, 95)), 
  Token::Terminator(string(1, 96)), 
  Token::Terminator(string(1, 97)), 
  Token::Terminator(string(1, 98)), 
  Token::Terminator(string(1, 99)), 
  Token::Terminator(string(1, 100)), 
  Token::Terminator(string(1, 101)), 
  Token::Terminator(string(1, 102)), 
  Token::Terminator(string(1, 103)), 
  Token::Terminator(string(1, 104)), 
  Token::Terminator(string(1, 105)), 
  Token::Terminator(string(1, 106)), 
  Token::Terminator(string(1, 107)), 
  Token::Terminator(string(1, 108)), 
  Token::Terminator(string(1, 109)), 
  Token::Terminator(string(1, 110)), 
  Token::Terminator(string(1, 111)), 
  Token::Terminator(string(1, 112)), 
  Token::Terminator(string(1, 113)), 
  Token::Terminator(string(1, 114)), 
  Token::Terminator(string(1, 115)), 
  Token::Terminator(string(1, 116)), 
  Token::Terminator(string(1, 117)), 
  Token::Terminator(string(1, 118)), 
  Token::Terminator(string(1, 119)), 
  Token::Terminator(string(1, 120)), 
  Token::Terminator(string(1, 121)), 
  Token::Terminator(string(1, 122)), 
  Token::Terminator(string(1, 123)), 
  Token::Terminator(string(1, 124)), 
  Token::Terminator(string(1, 125)), 
  Token::Terminator(string(1, 126)), 
  Token::Terminator(string(1, 127)), 
  Token::Terminator(string(1, 128)), 
  Token::Terminator(string(1, 129)), 
  Token::Terminator(string(1, 130)), 
  Token::Terminator(string(1, 131)), 
  Token::Terminator(string(1, 132)), 
  Token::Terminator(string(1, 133)), 
  Token::Terminator(string(1, 134)), 
  Token::Terminator(string(1, 135)), 
  Token::Terminator(string(1, 136)), 
  Token::Terminator(string(1, 137)), 
  Token::Terminator(string(1, 138)), 
  Token::Terminator(string(1, 139)), 
  Token::Terminator(string(1, 140)), 
  Token::Terminator(string(1, 141)), 
  Token::Terminator(string(1, 142)), 
  Token::Terminator(string(1, 143)), 
  Token::Terminator(string(1, 144)), 
  Token::Terminator(string(1, 145)), 
  Token::Terminator(string(1, 146)), 
  Token::Terminator(string(1, 147)), 
  Token::Terminator(string(1, 148)), 
  Token::Terminator(string(1, 149)), 
  Token::Terminator(string(1, 150)), 
  Token::Terminator(string(1, 151)), 
  Token::Terminator(string(1, 152)), 
  Token::Terminator(string(1, 153)), 
  Token::Terminator(string(1, 154)), 
  Token::Terminator(string(1, 155)), 
  Token::Terminator(string(1, 156)), 
  Token::Terminator(string(1, 157)), 
  Token::Terminator(string(1, 158)), 
  Token::Terminator(string(1, 159)), 
  Token::Terminator(string(1, 160)), 
  Token::Terminator(string(1, 161)), 
  Token::Terminator(string(1, 162)), 
  Token::Terminator(string(1, 163)), 
  Token::Terminator(string(1, 164)), 
  Token::Terminator(string(1, 165)), 
  Token::Terminator(string(1, 166)), 
  Token::Terminator(string(1, 167)), 
  Token::Terminator(string(1, 168)), 
  Token::Terminator(string(1, 169)), 
  Token::Terminator(string(1, 170)), 
  Token::Terminator(string(1, 171)), 
  Token::Terminator(string(1, 172)), 
  Token::Terminator(string(1, 173)), 
  Token::Terminator(string(1, 174)), 
  Token::Terminator(string(1, 175)), 
  Token::Terminator(string(1, 176)), 
  Token::Terminator(string(1, 177)), 
  Token::Terminator(string(1, 178)), 
  Token::Terminator(string(1, 179)), 
  Token::Terminator(string(1, 180)), 
  Token::Terminator(string(1, 181)), 
  Token::Terminator(string(1, 182)), 
  Token::Terminator(string(1, 183)), 
  Token::Terminator(string(1, 184)), 
  Token::Terminator(string(1, 185)), 
  Token::Terminator(string(1, 186)), 
  Token::Terminator(string(1, 187)), 
  Token::Terminator(string(1, 188)), 
  Token::Terminator(string(1, 189)), 
  Token::Terminator(string(1, 190)), 
  Token::Terminator(string(1, 191)), 
  Token::Terminator(string(1, 192)), 
  Token::Terminator(string(1, 193)), 
  Token::Terminator(string(1, 194)), 
  Token::Terminator(string(1, 195)), 
  Token::Terminator(string(1, 196)), 
  Token::Terminator(string(1, 197)), 
  Token::Terminator(string(1, 198)), 
  Token::Terminator(string(1, 199)), 
  Token::Terminator(string(1, 200)), 
  Token::Terminator(string(1, 201)), 
  Token::Terminator(string(1, 202)), 
  Token::Terminator(string(1, 203)), 
  Token::Terminator(string(1, 204)), 
  Token::Terminator(string(1, 205)), 
  Token::Terminator(string(1, 206)), 
  Token::Terminator(string(1, 207)), 
  Token::Terminator(string(1, 208)), 
  Token::Terminator(string(1, 209)), 
  Token::Terminator(string(1, 210)), 
  Token::Terminator(string(1, 211)), 
  Token::Terminator(string(1, 212)), 
  Token::Terminator(string(1, 213)), 
  Token::Terminator(string(1, 214)), 
  Token::Terminator(string(1, 215)), 
  Token::Terminator(string(1, 216)), 
  Token::Terminator(string(1, 217)), 
  Token::Terminator(string(1, 218)), 
  Token::Terminator(string(1, 219)), 
  Token::Terminator(string(1, 220)), 
  Token::Terminator(string(1, 221)), 
  Token::Terminator(string(1, 222)), 
  Token::Terminator(string(1, 223)), 
  Token::Terminator(string(1, 224)), 
  Token::Terminator(string(1, 225)), 
  Token::Terminator(string(1, 226)), 
  Token::Terminator(string(1, 227)), 
  Token::Terminator(string(1, 228)), 
  Token::Terminator(string(1, 229)), 
  Token::Terminator(string(1, 230)), 
  Token::Terminator(string(1, 231)), 
  Token::Terminator(string(1, 232)), 
  Token::Terminator(string(1, 233)), 
  Token::Terminator(string(1, 234)), 
  Token::Terminator(string(1, 235)), 
  Token::Terminator(string(1, 236)), 
  Token::Terminator(string(1, 237)), 
  Token::Terminator(string(1, 238)), 
  Token::Terminator(string(1, 239)), 
  Token::Terminator(string(1, 240)), 
  Token::Terminator(string(1, 241)), 
  Token::Terminator(string(1, 242)), 
  Token::Terminator(string(1, 243)), 
  Token::Terminator(string(1, 244)), 
  Token::Terminator(string(1, 245)), 
  Token::Terminator(string(1, 246)), 
  Token::Terminator(string(1, 247)), 
  Token::Terminator(string(1, 248)), 
  Token::Terminator(string(1, 249)), 
  Token::Terminator(string(1, 250)), 
  Token::Terminator(string(1, 251)), 
  Token::Terminator(string(1, 252)), 
  Token::Terminator(string(1, 253)), 
  Token::Terminator(string(1, 254)), 
  Token::Terminator(string(1, 255)), 
  Token::Terminator("CONSTANT"), // 256
  Token::Terminator("IDENTIFIER"), // 257
  Token::Terminator("IF"), // 258
  Token::Terminator("INT"), // 259
  Token::Terminator("RETURN"), // 260
  Token::Terminator("STRING_LITERAL"), // 261
  Token::NonTerminator("assignment_expression"), // 262
  Token::NonTerminator("block_item"), // 263
  Token::NonTerminator("block_item_list"), // 264
  Token::NonTerminator("compound_statement"), // 265
  Token::NonTerminator("declaration"), // 266
  Token::NonTerminator("declaration_specifiers"), // 267
  Token::NonTerminator("external_declaration"), // 268
  Token::NonTerminator("function_definition"), // 269
  Token::NonTerminator("init_declarator"), // 270
  Token::NonTerminator("init_declarator_list"), // 271
  Token::NonTerminator("translation_unit"), // 272
};

//@variable
auto &start_syntax_token = syntax_tokens[translation_unit];

/* section 4 */
// syntax
//@variable
vector<Production> productions = {
  // translation_unit : external_declaration ;
  Production(syntax_tokens[translation_unit], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[external_declaration]), 
  // translation_unit : translation_unit external_declaration ;
  Production(syntax_tokens[translation_unit], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[translation_unit])(syntax_tokens[external_declaration]), 
  // external_declaration : function_definition ;
  Production(syntax_tokens[external_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[function_definition]), 
  // external_declaration : declaration ;
  Production(syntax_tokens[external_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration]), 
  // function_definition : declaration_specifiers IDENTIFIER '(' ')' compound_statement ;
  Production(syntax_tokens[function_definition], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[IDENTIFIER])(syntax_tokens['('])(syntax_tokens[')'])(syntax_tokens[compound_statement]), 
  // compound_statement : '{' '}' ;
  Production(syntax_tokens[compound_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['{'])(syntax_tokens['}']), 
  // compound_statement : '{' block_item_list '}' ;
  Production(syntax_tokens[compound_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['{'])(syntax_tokens[block_item_list])(syntax_tokens['}']), 
  // block_item_list : block_item ;
  Production(syntax_tokens[block_item_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[block_item]), 
  // block_item_list : block_item_list block_item ;
  Production(syntax_tokens[block_item_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[block_item_list])(syntax_tokens[block_item]), 
  // block_item : declaration ;
  Production(syntax_tokens[block_item], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration]), 
  // declaration : declaration_specifiers init_declarator_list ';' ;
  Production(syntax_tokens[declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[init_declarator_list])(syntax_tokens[';']), 
  // declaration_specifiers : INT ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[INT]), 
  // init_declarator_list : init_declarator ;
  Production(syntax_tokens[init_declarator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[init_declarator]), 
  // init_declarator_list : init_declarator_list ',' init_declarator ;
  Production(syntax_tokens[init_declarator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[init_declarator_list])(syntax_tokens[','])(syntax_tokens[init_declarator]), 
  // init_declarator : IDENTIFIER ;
  Production(syntax_tokens[init_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER]), 
  // init_declarator : IDENTIFIER '=' assignment_expression ;
  Production(syntax_tokens[init_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER])(syntax_tokens['='])(syntax_tokens[assignment_expression]), 
  // assignment_expression : IDENTIFIER ;
  Production(syntax_tokens[assignment_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER]), 
  // assignment_expression : CONSTANT ;
  Production(syntax_tokens[assignment_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[CONSTANT]), 
  // assignment_expression : STRING_LITERAL ;
  Production(syntax_tokens[assignment_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[STRING_LITERAL]), 
};

// lexical
vector<Token> lexical_tokens = {
  Token::Terminator(R"((if))"), 
  Token::Terminator(R"((int))"), 
  Token::Terminator(R"((return))"), 
  Token::Terminator(R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)"), 
  Token::Terminator(R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)"), 
  Token::Terminator(R"(L?"(\\.|[^\\"\r\n])*")"), 
  Token::Terminator(R"((;))"), 
  Token::Terminator(R"((({)|(<%)))"), 
  Token::Terminator(R"(((})|(%>)))"), 
  Token::Terminator(R"((=))"), 
  Token::Terminator(R"((\())"), 
  Token::Terminator(R"((\)))"), 
  Token::Terminator(R"((-))"), 
  Token::Terminator(R"((\+))"), 
  Token::Terminator(R"((\*))"), 
  Token::Terminator(R"((/))"), 
  Token::Terminator(R"([ \t\v\r\n\f])"), 
  Token::Terminator(R"(.)"), 
};
vector<RegEx> lexical_tokens_regex = {
  RegEx(R"((if))"), 
  RegEx(R"((int))"), 
  RegEx(R"((return))"), 
  RegEx(R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)"), 
  RegEx(R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)"), 
  RegEx(R"(L?"(\\.|[^\\"\r\n])*")"), 
  RegEx(R"((;))"), 
  RegEx(R"((({)|(<%)))"), 
  RegEx(R"(((})|(%>)))"), 
  RegEx(R"((=))"), 
  RegEx(R"((\())"), 
  RegEx(R"((\)))"), 
  RegEx(R"((-))"), 
  RegEx(R"((\+))"), 
  RegEx(R"((\*))"), 
  RegEx(R"((/))"), 
  RegEx(R"([ \t\v\r\n\f])"), 
  RegEx(R"(.)"), 
};


/* section 5 */
void count() {
  // pass
}

void comment() {
  // pass
}

int check_type(void)
{
  return IDENTIFIER;
}

/* section 5.1 */



/* section 6 */
//@variable
IdType to_syntax_token_id(Token lexical_token, AttrDict &ad) {
  string token_name = lexical_token.GetTokName();
  if (token_name == R"((if))") { 
    { { count(); return(IF); }}
  } else if (token_name == R"((int))") { 
    { { count(); return(INT); }}
  } else if (token_name == R"((return))") { 
    { { count(); return(RETURN); }}
  } else if (token_name == R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)") { 
    { { count(); return(IDENTIFIER); }}
  } else if (token_name == R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(L?"(\\.|[^\\"\r\n])*")") { 
    { { count(); return(STRING_LITERAL); }}
  } else if (token_name == R"((;))") { 
    { { count(); return(';'); }}
  } else if (token_name == R"((({)|(<%)))") { 
    { { count(); return('{'); }}
  } else if (token_name == R"(((})|(%>)))") { 
    { { count(); return('}'); }}
  } else if (token_name == R"((=))") { 
    { { count(); return('='); }}
  } else if (token_name == R"((\())") { 
    { { count(); return('('); }}
  } else if (token_name == R"((\)))") { 
    { { count(); return(')'); }}
  } else if (token_name == R"((-))") { 
    { { count(); return('-'); }}
  } else if (token_name == R"((\+))") { 
    { { count(); return('+'); }}
  } else if (token_name == R"((\*))") { 
    { { count(); return('*'); }}
  } else if (token_name == R"((/))") { 
    { { count(); return('/'); }}
  } else if (token_name == R"([ \t\v\r\n\f])") { 
    { { count(); }}
  } else if (token_name == R"(.)") { 
    { { /* Add code to complain about unmatched characters */ }}
  } else  {
    return 0;
  }
  return 0;
}

/* section 7 */
int main() {
  /* section 7.1 */
  spdlog::set_level(spdlog::level::info);
  
  /* section 7.2 */
  // lexical token
  //@variable

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

  cout << start_syntax_token.GetTokName() << endl;

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

  return 0;
}
