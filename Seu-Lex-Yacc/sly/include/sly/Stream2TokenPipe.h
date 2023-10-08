//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_STREAM2TOKENPIPE_H
#define SEULEXYACC_STREAM2TOKENPIPE_H

#include "def.h"
#include "Token.h"
#include "AttrDict.h"
#include <iostream>
#include <string>
#include <vector>

namespace sly::runtime {

class Stream2TokenPipe {
 public:
  explicit Stream2TokenPipe() {};
  explicit Stream2TokenPipe(std::vector<std::vector<int>> working_table, 
    std::vector<int> accept_states, std::vector<core::type::Token> corr_token, core::type::Token end_token);

  core::type::Token Defer(std::istream& is);

  void SetIngore(std::vector<core::type::Token> ignored_token);

  std::string buffer_;

  int row_;
  int col_;

  int token_begin_row_;
  int token_begin_col_;
  int token_end_row_;
  int token_end_col_;

  char input(std::istream& is);
  void unput(std::istream& is, char c); 

 private:

  std::string history_;
  int history_count_;

  int row_prev_;
  int col_prev_;

  std::vector<std::vector<int>> table_;
  
  std::vector<int> accept_states_;

  vector<core::type::Token> token_list_;

  core::type::Token end_token_;
};

} // namespace sly::runtime
#endif