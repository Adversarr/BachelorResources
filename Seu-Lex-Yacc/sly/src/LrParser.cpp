#include "sly/Token.h"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/spdlog.h"
#include <sly/LrParser.h>
#include <sly/utils.h>
#include <stdexcept>

namespace sly::core::grammar {

const ParsingTable &LrParser::GetPt() const { return pt_; }

void LrParser::SetPt(const ParsingTable &pt) { pt_ = pt; }

LrParser::LrParser(ParsingTable &parsing_table)
    : pt_(parsing_table), current_state_id_(-1), current_offset_(0),
      state_stack_(1, 0) {}

void LrParser::Parse(vector<Token> token_stream,
                     vector<YYSTATE> yylval_stream) {
  if (token_stream.back() != pt_.GetEndingToken()) {
    if (token_stream.back() != pt_.GetEndingToken()) {
      spdlog::warn("Input token stream does not end with {} so add to it.",
                   pt_.GetEndingToken().ToString());
      token_stream.push_back(pt_.GetEndingToken());
      yylval_stream.emplace_back();
    }
  }
  apt_stack_.clear();
  state_stack_.clear();
  current_offset_ = 0;
  state_stack_ = std::deque<IdType>(1, 0);
  accepted_ = false;
  while (current_offset_ < token_stream.size() && !accepted_) {
    ParseOnce(token_stream, yylval_stream);
  }

  spdlog::debug("Lr Parse Done.");
  while (current_offset_ < token_stream.size()) {
    if (token_stream[current_offset_] != pt_.GetEndingToken()) {
      spdlog::warn("Token Stream Not Empty!: {} ({} left).",
                  token_stream[current_offset_].ToString(),
                  token_stream.size() - current_offset_ - 1);
    }
    ++current_offset_;
  }
}

void LrParser::ParseStep(const vector<Token> &token_stream,
                         const vector<YYSTATE> &yylval_stream) {
  while (current_offset_ < token_stream.size()) {
    ParseOnce(token_stream, yylval_stream);
  }
}

void LrParser::ParseOnce(const vector<Token> &token_stream,
                         const vector<YYSTATE> &yylval_stream) {
  auto &current_token = token_stream[current_offset_];
  auto &current_attr = yylval_stream[current_offset_];
  if (current_token.GetTokenType() == Token::Type::kEpsilon) {
    current_offset_ += 1;
    return;
  } else if (current_token.GetTokenType() == Token::Type::kTerminator) {
    const auto &act = pt_.GetAction(state_stack_.back(), current_token);
    if (act.size() != 1) {
      spdlog::error("Found invalid action table.");
      throw runtime_error("Found invalid action table.");
    }
    const auto &action = act[0];
    if (action.action == ParsingTable::kShiftIn) {
      // 执行移入操作
      apt_stack_.emplace_back(current_token, yylval_stream[current_offset_]);
      // 当前位置 + 1
      current_offset_ += 1;
      // 当前状态更新
      state_stack_.emplace_back(action.id);
      spdlog::debug("Shift In [{}]], Go state {}", current_token.ToString(),
                    state_stack_.back());
    } else if (action.action == ParsingTable::kReduce) {
      // 按照 id 进行规约
      const auto &prod = pt_.GetProductions()[action.id];
      AnnotatedParseTree apt(prod);
      for (int i = 1; i < prod.GetTokens().size(); ++i) {
        apt.EmplaceFront(move(apt_stack_.back()));
        apt_stack_.pop_back();
        state_stack_.pop_back();
      }
      apt_stack_.emplace_back(apt);
      const auto &go =
          pt_.GetGoto(state_stack_.back(), prod.GetTokens().front());
      if (go.size() != 1) {
        spdlog::error("Found invalid goto. from {} to {}", state_stack_.back(),
                      prod.GetTokens().front().ToString());
        throw runtime_error(fmt::format("Found invalid goto. from {} to {}",
                                        state_stack_.back(),
                                        prod.GetTokens().front().ToString()));
      }
      state_stack_.emplace_back(go[0]);
      spdlog::debug("Reduce [{}], Go state {}", current_token.ToString(),
                    state_stack_.back());

    } else {
      if (action.action == ParsingTable::kAccept) {
        current_offset_ += 1;
        accepted_ = true;
        return;
      }
      if (action.action == ParsingTable::kError) {
        if (current_token != pt_.GetEndingToken()) {
          spdlog::error("{}:{}: \033[31msyntax error:\033[0m "
                        "caught unexpected token {} at line {} column {}, ",
                        __FILE__, __LINE__, current_token.ToString(),
                        current_attr.Get<int>("row"),
                        current_attr.Get<int>("col"));
        } else {
          spdlog::error("{}:{}: \033[31msyntax error:\033[0m "
                        "caught unexpected token {} at the end of file, ",
                        __FILE__, __LINE__, current_token.ToString());
        }
        spdlog::error("current token={}", current_token.ToString());
        // spdlog::error("current state_stack={}",
        // utils::ToString{}(state_stack_)); spdlog::error("current
        // state_id={}", utils::ToString{}(current_state_id_));
        // spdlog::error("current apt_stack is:\n{}",
        // utils::ToString{}(apt_stack_));
        auto b = token_stream.cbegin() + max(0, (int)current_state_id_ - 5);
        auto e = token_stream.end();
        if (distance(b, token_stream.end()) >= 10) {
          e = b + 10;
        }
        spdlog::error("token stream = [... {} {}]",
                      utils::ToString{}(vector<Token>{b, e}),
                      current_token.ToString());
        exit(1);
      }
    }
  } else {
    spdlog::error(
        "{}:{}: \033[31msyntax error:\033[0m "
        "found non terminator {} in token_stream  at line {} column {}, ",
        __FILE__, __LINE__, current_token.ToString(), current_token.ToString(),
        current_attr.Get<int>("row"), current_attr.Get<int>("col"));
    spdlog::error("current token={}", current_token.ToString());
    auto b = token_stream.cbegin() + max(0, (int)current_state_id_ - 5);
    auto e = token_stream.end();
    if (distance(b, token_stream.end()) >= 10) {
      e = b + 10;
    }
    spdlog::error("token stream = [... {} {}]",
                  utils::ToString{}(vector<Token>{b, e}),
                  current_token.ToString());
    exit(1);
  }
}

AnnotatedParseTree LrParser::GetTree() const { return apt_stack_.front(); }

} // namespace sly::core::grammar