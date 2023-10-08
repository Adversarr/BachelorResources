/**
 * @file lex_lr.cpp
 * @author Jerry Yang (213190186@seu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-04-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "sly/Production.h"
#include "sly/RegEx.h"
#include <iostream>
#include <sly/sly.h>
#include <vector>

using namespace sly::core::type;
using namespace sly::core::grammar;
using namespace std;



auto regex_shorthand = Token::NonTerminator("re-shorthand");
std::vector<Production> productions = {
  Production()
};
int main() {
  sly::utils::Log::SetLogLevel(sly::utils::Log::kNone);
  sly::core::lexical::RegEx float_with_exp("[0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?");
  sly::core::lexical::RegEx s2("-=");
  sly::core::lexical::RegEx s3("--");
  sly::core::lexical::RegEx s4("->");
  cout << boolalpha << float_with_exp.CanMatch("1e9f") << endl;
  cout << boolalpha << s2.CanMatch("-=") << endl;
  cout << boolalpha << s3.CanMatch("--") << endl;
  cout << boolalpha << s4.CanMatch("->") << endl;
  return 0;
}