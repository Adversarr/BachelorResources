#include "sly/Token.h"
#include "spdlog/spdlog.h"
#include <cassert>
#include <sly/Stream2TokenPipe.h>
#include <sly/utils.h>
#include <stdexcept>

namespace sly::runtime {

Stream2TokenPipe::Stream2TokenPipe(std::vector<std::vector<int>> working_table,
                                   std::vector<int> accept_states,
                                   std::vector<core::type::Token> corr_token,
                                   core::type::Token end_token)
    : table_(move(working_table)), accept_states_(move(accept_states)),
      end_token_(move(end_token)), token_list_(move(corr_token)), 
      row_(1), col_(1), row_prev_(1), col_prev_(1) {
  for (const auto &v : accept_states_) {
    assert(v == -1 || v < accept_states_.size());
  }
  history_.clear();
  history_count_=0;
}

char Stream2TokenPipe::input(std::istream& is) {
  if (!(is.good() && !is.eof() && !is.fail())) {
    return 0; // file end
  } else {
    char c = is.get();
    spdlog::debug(
      "Caught ascii={} char={} From stream.", 
      static_cast<int>(c), c
    );
    row_prev_ = row_;
    col_prev_ = col_;
    if (c == '\n') {
      col_ = 1;
    } else if (c == '\r') {
      col_ = 1;
      row_ ++;
    } else if (c == '\t') {
      col_ += (8 - ((col_ - 1) % 8)) + 1;
    } else {
      col_ ++;
    }
    return c;
  }
}

void Stream2TokenPipe::unput(std::istream &is, char c) {
  is.putback(c);
  row_ = row_prev_;
  col_ = col_prev_;
}

core::type::Token Stream2TokenPipe::Defer(std::istream &is) {
  int current_state = 0;
  char c;
  buffer_.clear();
  token_begin_row_ = row_;
  token_begin_col_ = col_;

  if (!(is.good() && !is.eof() && !is.fail())) {
    return end_token_;
  }
  while (is.good() && !is.eof() && !is.fail()) {
    if (history_.size() > 20) {
      history_ = history_.substr(10);
    }
    // c = is.get();
    c = input(is);
    spdlog::debug("Caught ascii={} char={} From stream.", static_cast<int>(c),
                 c);
    // 1. 测试是否是可行的
    if (!(c > static_cast<int8_t>(0) && c <= static_cast<int8_t>(127))) {
      spdlog::debug("Handling the eof flag.");
      if (buffer_.length() == 0) {
        // 如果 buffer 是空的，直接返回 eof 标志
        return end_token_;
      } else {
        // 如果 buffer 不空，则先返回之前的内容，并把 c 放回。
        unput(is, c);
        break;
      }
    }
    int next_state = table_[current_state][c];
    if (next_state == -1) {
      // flush buffer and return
      unput(is, c);
      break;
    } else {
      spdlog::debug("Push to buffer.");
      buffer_.push_back(c);
      history_.push_back(c);
      history_count_ ++;
      current_state = next_state;
    }
  }
  token_end_row_ = row_;
  token_end_col_ = col_;

  // 显然当前 buffer 不空
  int return_token_id = accept_states_[current_state];
  if (return_token_id < 0) {
    spdlog::error("{}:{}: \033[31mlexical error:\033[0m", __FILE__, __LINE__);
    spdlog::error("caught invalid element '\033[33m{}\033[0m' (ascii={}) at line {} column {}", 
                  c, static_cast<int>(c), row_+1, col_+1);
    spdlog::error("current_buffer=\"\033[33m{}\033[0m\"", sly::utils::escape(buffer_));
    spdlog::error("history_=\"\033[33m{}\033[0m\"", sly::utils::escape(history_));
    exit(1);
  } else {
    spdlog::info("return: buffer={} corr={}", buffer_, token_list_[return_token_id].ToString());
  }
  return token_list_[return_token_id];
}

} // namespace sly::runtime