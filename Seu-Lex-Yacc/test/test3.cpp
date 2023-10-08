#include "sly/FaModel.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include "sly/Token.h"
#include <sly/sly.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using sly::core::type::AttrDict;
using sly::core::type::Token;
using sly::core::lexical::RegEx;
using sly::core::lexical::DfaModel;
using sly::runtime::Stream2TokenPipe;
using namespace std;

vector<string> regex_strings = {
  R"((/\*))", R"((//)[^\n]*)", R"((auto))", R"((_Bool))", R"((break))", 
  R"((case))", R"((char))", R"((_Complex))", R"((const))", R"((continue))", 
  R"((default))", R"((do))", R"((double))", R"((else))", R"((enum))", R"((extern))", 
  R"((float))", R"((for))", R"((goto))", R"((if))", R"((_Imaginary))", R"((inline))", 
  R"((int))", R"((long))", R"((register))", R"((restrict))", R"((return))", 
  R"((short))", R"((signed))", R"((sizeof))", R"((static))", R"((struct))", 
  R"((switch))", R"((typedef))", R"((union))", R"((unsigned))", R"((void))", 
  R"((volatile))", R"((while))", R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)", 
  R"(0[xX][a-fA-F0-9]+((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)", 
  R"(0[0-7]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)", 
  R"([1-9][0-9]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)", 
  R"(L?'(\\.|[^\\'\n])+')", R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)", 
  R"([0-9]*(\.)[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?)", 
  R"([0-9]+(\.)[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?)", 
  R"(0[xX][a-fA-F0-9]+([Pp][+-]?[0-9]+)(f|F|l|L)?)", 
  R"(0[xX][a-fA-F0-9]*(\.)[a-fA-F0-9]+([Pp][+-]?[0-9]+)?(f|F|l|L)?)", 
  R"(0[xX][a-fA-F0-9]+(\.)[a-fA-F0-9]*([Pp][+-]?[0-9]+)?(f|F|l|L)?)", 
  R"(L?"(\\.|[^\\"\n])*")", R"((\.\.\.))", R"((>>=))", R"((<<=))", R"((\+=))", 
  R"((-=))", R"((\*=))", R"((/=))", R"((%=))", R"((&=))", R"((\^=))", R"((\|=))", 
  R"((>>))", R"((<<))", R"((\+\+))", R"((--))", R"((->))", R"((&&))", R"((\|\|))", 
  R"((<=))", R"((>=))", R"((==))", R"((!=))", R"((;))", R"((({)|(<%)))", 
  R"(((})|(%>)))", R"((,))", R"((:))", R"((=))", R"((\())", R"((\)))", 
  R"(((\[)|(<:)))", R"(((\])|(:>)))", R"((\.))", R"((&))", R"((!))", R"((~))", 
  R"((-))", R"((\+))", R"((\*))", R"((/))", R"((%))", R"((<))", R"((>))", R"((\^))", 
  R"((\|))", R"((?))", R"([ \t\v\n\f])", R"(.)", 
};

int main() {
  sly::utils::Log::SetLogLevel(sly::utils::Log::kError);

  auto ending = Token::Terminator("EOF_FLAG");
  // TODO: 原来的代码：
  // vector<Token> lexical_tokens = {
  //   Token::Terminator("any"),
  //   Token::Terminator("word"),
  // };
  // vector<RegEx> lexical_tokens_regex = {
  //   RegEx("."),
  //   RegEx("([a-zA-Z_]([a-zA-Z_]|[0-9])*)"), 
  // };
  vector<Token> lexical_tokens = {
    Token::Terminator("integer"),
    Token::Terminator("float"),
    Token::Terminator("kw-auto"),
    Token::Terminator("kw-const"),
    Token::Terminator("kw-void"),
    Token::Terminator("identifier"),
    Token::Terminator("eq"),
    Token::Terminator("minus-and-assign"),
    Token::Terminator("semicolon"),
    Token::Terminator("post-self-plus"),
    Token::Terminator("lbrace"),
    Token::Terminator("rbrace"),
    Token::Terminator("line-comment"),
    Token::Terminator("spaces"),
    Token::Terminator("any"),
  };
  vector<RegEx> lexical_tokens_regex = {
    RegEx("(([0-9])+)"),
    RegEx("([0-9]+)\\.([0-9]*)(e[+-]?[0-9]+)?"),
    RegEx("auto"),
    RegEx("const"),
    RegEx("void"),
    RegEx("([a-zA-Z_]([a-zA-Z_]|[0-9])*)"), 
    RegEx("="),
    RegEx("-="),
    RegEx(";"),
    RegEx("\\+\\+"),
    RegEx("\\)"),
    RegEx("\\("),
    RegEx("//[^\n]*"),
    RegEx("(\r|\n|\t| )+"),
    RegEx("."),
  };
  vector<DfaModel> lexical_tokens_dfa;
  for (auto& regex : lexical_tokens_regex) {
    lexical_tokens_dfa.push_back(regex.GetDfaModel());
  }
  auto [transition, state] = DfaModel::Merge(lexical_tokens_dfa);
  auto s2ppl = Stream2TokenPipe(transition, state, lexical_tokens, ending);


  string input_string = "abc";
  // 测试样例
  // string s = R"(
  //   auto a = 1.0e2; // this is a comment.
  //   const int b = 2;
  //   b++;
  //   const int bca_123 = 4.0e-10;
  //   void abc();
  // )";
  cin >> input_string;
  stringstream input_stream(input_string);

  vector<AttrDict> attributes;
  vector<Token> tokens;
  while (true) {
    string input_string;
    getline(cin, input_string);
    stringstream input_stream(input_string);

    cerr << setw(12) << "\"" + ad.Get<string>("lval") + "\""
         << "\t" << token.GetTokName() << endl;

    while (true) {
      auto token = s2ppl.Defer(input_stream);
      if (token == ending)
        break;
      AttrDict ad;
      ad.Set("lval", s2ppl.buffer_); 

      cerr << ad.Get<string>("lval") << " -> [" << token.GetTokName() << "]" << endl;
    }
  }
  
  return 0;
}