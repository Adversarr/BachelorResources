#include "sly/FaModel.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include "sly/Token.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <ios>
#include <iostream>
#include <sly/sly.h>
#include <sstream>

using sly::core::grammar::LrParser;
using sly::core::lexical::DfaModel;
using sly::core::lexical::RegEx;
using sly::core::type::AttrDict;
using sly::core::type::Production;
using sly::core::type::Token;
using sly::runtime::Stream2TokenPipe;
using namespace std;

vector<string> regex_strings = {
    R"((/\*))",
    R"((//)[^\n]*)",
    R"((auto))",
    R"((_Bool))",
    R"((break))",
    R"((case))",
    R"((char))",
    R"((_Complex))",
    R"((const))",
    R"((continue))",
    R"((default))",
    R"((do))",
    R"((double))",
    R"((else))",
    R"((enum))",
    R"((extern))",
    R"((float))",
    R"((for))",
    R"((goto))",
    R"((if))",
    R"((_Imaginary))",
    R"((inline))",
    R"((int))",
    R"((long))",
    R"((register))",
    R"((restrict))",
    R"((return))",
    R"((short))",
    R"((signed))",
    R"((sizeof))",
    R"((static))",
    R"((struct))",
    R"((switch))",
    R"((typedef))",
    R"((union))",
    R"((unsigned))",
    R"((void))",
    R"((volatile))",
    R"((while))",
    R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)",
    R"(0[xX][a-fA-F0-9]+((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)",
    R"(0[0-7]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)",
    R"([1-9][0-9]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)",
    R"(L?'(\\.|[^\\'\n])+')",
    R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)",
    R"([0-9]*(\.)[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?)",
    R"([0-9]+(\.)[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?)",
    R"(0[xX][a-fA-F0-9]+([Pp][+-]?[0-9]+)(f|F|l|L)?)",
    R"(0[xX][a-fA-F0-9]*(\.)[a-fA-F0-9]+([Pp][+-]?[0-9]+)?(f|F|l|L)?)",
    R"(0[xX][a-fA-F0-9]+(\.)[a-fA-F0-9]*([Pp][+-]?[0-9]+)?(f|F|l|L)?)",
    R"(L?"(\\.|[^\\"\n])*")",
    R"((\.\.\.))",
    R"((>>=))",
    R"((<<=))",
    R"((\+=))",
    R"((-=))",
    R"((\*=))",
    R"((/=))",
    R"((%=))",
    R"((&=))",
    R"((\^=))",
    R"((\|=))",
    R"((>>))",
    R"((<<))",
    R"((\+\+))",
    R"((--))",
    R"((->))",
    R"((&&))",
    R"((\|\|))",
    R"((<=))",
    R"((>=))",
    R"((==))",
    R"((!=))",
    R"((;))",
    R"((({)|(<%)))",
    R"(((})|(%>)))",
    R"((,))",
    R"((:))",
    R"((=))",
    R"((\())",
    R"((\)))",
    R"(((\[)|(<:)))",
    R"(((\])|(:>)))",
    R"((\.))",
    R"((&))",
    R"((!))",
    R"((~))",
    R"((-))",
    R"((\+))",
    R"((\*))",
    R"((/))",
    R"((%))",
    R"((<))",
    R"((>))",
    R"((\^))",
    R"((\|))",
    R"((?))",
    R"([ \t\v\n\f])",
    R"(.)",
};



int main() {
  spdlog::set_level(spdlog::level::warn);
  sly::utils::Log::SetLogLevel(sly::utils::Log::kError);
  auto ending = Token::Terminator("EOF_FLAG");
  vector<Token> lexical_tokens;
  vector<DfaModel> lexical_tokens_dfa;
  for (string str : regex_strings) {
    lexical_tokens.push_back(Token::Terminator(str));
    cerr << "make " << str;
    lexical_tokens_dfa.push_back(RegEx(str).GetDfaModel());
    cerr << " successfully" << endl;
  }
  auto [transition, state] = DfaModel::Merge(lexical_tokens_dfa);
  auto s2ppl = Stream2TokenPipe(transition, state, lexical_tokens, ending);

  cerr << "start testing" << endl;
  while (true) {
    string input_string;
    getline(cin, input_string);
    stringstream input_stream(input_string);
    cerr << input_string << endl;
    while (true) {
      auto token = s2ppl.Defer(input_stream);
      if (token == ending)
        break;
      AttrDict ad;
      ad.Set("lval", s2ppl.buffer_);

      cerr << ad.Get<string>("lval") << " -> [" << token.GetTokName() << "]"
           << endl;
    }
  }

  return 0;
}
