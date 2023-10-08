/**
 * @file test2.cpp
 * @author Jerry Yang (213190186@seu.edu.cn)
 * @brief 测试 Regex 输出情况
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "sly/FaModel.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include "spdlog/spdlog.h"
#include <sly/sly.h>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  sly::core::lexical::RegEx r1("123");
  sly::core::lexical::RegEx r2("ab*d+");
  sly::core::lexical::RegEx r3("[a-z]+");
  sly::core::lexical::RegEx r4(" |\n");
  auto end_token = Token::Terminator("end");
  auto ret = sly::core::lexical::DfaModel::Merge({r1.GetDfaModel(), r2.GetDfaModel(), 
    r3.GetDfaModel(), r4.GetDfaModel()});
  sly::runtime::Stream2TokenPipe s2ppl(
    ret.first, ret.second, {
      Token::Terminator("123"),
      Token::Terminator("ab*d+"),
      Token::Terminator("[a-z]+"),
      Token::Terminator(" |\n")
    }, end_token
  );
  istringstream iss("123 abd zbdc");
  while (true) {
    auto tok = s2ppl.Defer(iss);
    cout << tok << endl;
    if (tok == end_token) {
      spdlog::info("Done.");
      return 0;
    }
  }
  return 0;
}