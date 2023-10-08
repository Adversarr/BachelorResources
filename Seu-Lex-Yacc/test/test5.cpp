// 
// example of the output code file
// @variable indicates the position for replacement
// 
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

/* @variable */
const int num_lexical_tokens = 2;
const int num_syntax_tokens = 3;

auto ending = Token::Terminator("EOF_FLAG");

/* @variable */
#define AUTO 256
#define primary_expression 257
#define postfix_expression 258

// lexical
/* @variable */
vector<RegEx> lexical_tokens_regex_str = {
  RegEx{"auto"}, 
  RegEx{"\\+"}, 
};
/* @variable */
vector<Token> lexical_tokens = {
  Token::Terminator("auto"), 
  Token::Terminator("+"), 
};

// syntax
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
  Token::Terminator(string(1, 255)),            // 255 
  Token::Terminator("AUTO"),                    // 256
  Token::NonTerminator("primary_expression"),   // 257
  Token::NonTerminator("postfix_expression"),   // 258
};

auto &start_syntax_token = syntax_tokens[primary_expression];

/* @variable */
vector<Production> productions = {
  // primary_expression : AUTO postfix_expression ; 
  Production(syntax_tokens[primary_expression], {[](vector<YYSTATE> &v) {
      // ...
  }})(syntax_tokens[AUTO])(syntax_tokens[postfix_expression]), 
  // postfix_expression : AUTO ; 
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // ...
  }})(syntax_tokens[AUTO]), 
};

void count() {
  // pass
}

/* @variable */
IdType to_syntax_token_id(Token lexical_token, AttrDict &ad) {
  string token_name = lexical_token.GetTokName();
  if (token_name == "auto") {
    { count(); return(AUTO); }
  } else if (token_name == "+") {
    { count(); return('+'); }
  }
}

int main() {
  sly::utils::Log::SetLogLevel(sly::utils::Log::kError);
  // BUG: RegEx cannot be defined before runtime
  vector<RegEx> lexical_tokens_regex = {
    RegEx("auto"), 
    RegEx("\\+"), 
  };
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

  // runtime
  string input_string = "autoauto";
  stringstream input_stream(input_string);

  vector<AttrDict> attributes;
  vector<Token> tokens;
  while (true) {
    auto lexical_token = s2ppl.Defer(input_stream);
    if (lexical_token == ending)
      break;
    AttrDict ad;
    ad.Set("lval", s2ppl.buffer_); 
    ad.Set<int>("row", 1);
    ad.Set<int>("col", 1);
    IdType id = to_syntax_token_id(lexical_token, ad);
    if (lexical_token == ending) {
      break;
    }
    Token syntax_token = syntax_tokens[id];

    tokens.emplace_back(syntax_token);
    attributes.emplace_back(ad);
    
    
  }

  cerr << "tokens: " << endl;
  for (auto token : tokens) {
    cerr << "  " << token.GetTokName() << endl;
  }


  parser.Parse(tokens, attributes);
  auto tree = parser.GetTree();
  cerr << "parse tree: " << endl;
  tree.Print(std::cerr);

  return 0;
}
