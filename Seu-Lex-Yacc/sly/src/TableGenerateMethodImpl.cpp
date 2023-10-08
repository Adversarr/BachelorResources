//
// Created by Yang Jerry on 2022/3/30.
//

#include "spdlog/spdlog.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sly/TableGenerateMethodImpl.h>
#include <sly/utils.h>
#include <sstream>

namespace sly::core::grammar {

void Lr1::Defer(const ContextFreeGrammar &cfg) {
  p_grammar = &cfg;
  GenFirst();
  GenFollow();
  GenItemGo();
  GenTable();
}

optional<unordered_set<LRItem, LRItem::Hash>>
Lr1::Lr1GotoFunc(const LRItemSet &lrs, const Token &tok) const {
  LRItemSet retval;
  for (const auto &lri : lrs) {
    auto deferred = lri.Defer(tok);
    if (deferred.has_value())
      retval.insert(deferred.value());
  }
  if (retval.empty())
    return optional<LRItemSet>{};
  else
    return make_optional(Lr1Closure(retval));
}

void Lr1::GenFirst() {
  FUNC_START_INFO;
  bool changed = true;
  first_set_.clear();
  for (const auto &tok : p_grammar->GetNonTerminators()) {
    // First [ Non-Term ] init as Empty
    first_set_.insert({tok, {}});
  }
  for (const auto &tok : p_grammar->GetTerminators()) {
    // First [ Term ] === Term
    first_set_.insert({tok, {tok}});
  }
  int iter = 0;
  while (changed) {
    changed = false;
    for (auto &prod : p_grammar->GetProductions()) {
      // ForEach Production, Update the first set of `lhs`
      auto &tokens = prod.GetTokens();
      auto &lhs = tokens.front();
      auto first_updated = GetFirst(tokens.cbegin() + 1, tokens.cend());
      auto &current = first_set_[lhs];
      for (auto &v : first_updated) {
        if (current.find(v) == current.end()) {
          current.insert(v);
          changed = true;
        }
      }
    }
  }
#ifndef NDEBUG
  for (const auto &[k, v] : first_set_) {
    ostringstream ss;
    ss << "First [" << k << "]: ";
    copy(v.begin(), v.end(), ostream_iterator<decltype(v)::value_type>(ss));
    spdlog::debug("{}", ss.str());
  }
#endif
  FUNC_END_INFO;
}

void Lr1::GenFollow() {
  FUNC_START_INFO;
  follow_set_.clear();
  if (first_set_.empty())
    throw runtime_error("Calculate first set first!");
  for (auto &tok : p_grammar->GetNonTerminators()) {
    follow_set_.insert({tok, {}});
  }

  follow_set_[p_grammar->GetAugmentedToken()].insert(
      p_grammar->GetEndingToken());

  bool changed = true;
  while (changed) {
    changed = false;
    for (auto &[tok, curr_follow] : follow_set_) {
      for (const auto &prod : p_grammar->GetProductions()) {
        const auto &follow_lhs = follow_set_[prod.GetTokens().front()];
        for (auto it = prod.GetTokens().cbegin() + 1;
             it != prod.GetTokens().cend(); it++) {
          if (*it == tok) {
            auto rest_first = GetFirst(it + 1, prod.GetTokens().cend());
            if (rest_first.find(p_grammar->GetEpsilonToken()) !=
                rest_first.end()) {
              rest_first.erase(p_grammar->GetEpsilonToken());
              rest_first.insert(follow_lhs.begin(), follow_lhs.end());
            }
            for (auto &t : rest_first) {
              if (curr_follow.find(t) == curr_follow.end()) {
                changed = true;
                curr_follow.insert(t);
              }
            }
          }
        }
      }
    }
  }
#ifndef NDEBUG
  for (const auto &[k, v] : follow_set_) {
    ostringstream ss;
    ss << "Follow [" << k << "]: ";
    copy(v.begin(), v.end(), ostream_iterator<decltype(v)::value_type>(ss));
    spdlog::debug("{}", ss.str());
  }
  FUNC_END_INFO;
#endif
}

void Lr1::GenItemGo() {
  FUNC_START_INFO;
  // 按照 LR1 推导所有产生式
  lr_item_set_.push_back(Lr1Closure(
      {LRItem({p_grammar->GetAugmentedToken(), p_grammar->GetEntryToken()},
              {p_grammar->GetEndingToken()})}));

  for (IdType i = 0; i < lr_item_set_.size(); i++) {
    // 创建当前的map
    item_go_map_.emplace_back();
    auto &curr_go = item_go_map_.back();
    // 更新方法
    auto upd_f = [&curr_go, this, i](const Token &tok) {
      auto &curr_lrs = lr_item_set_[i];
      auto gone = Lr1GotoFunc(curr_lrs, tok);

      if (!gone.has_value())
        return;
#ifndef NDEBUG
      stringstream ss;
      for (auto &lri : gone.value()) {
        copy(lri.GetTokens().begin(), lri.GetTokens().end(),
             ostream_iterator<Token>(ss, ", "));
      }
#endif
      auto pos = find(lr_item_set_.begin(), lr_item_set_.end(), gone.value());

      IdType new_id = distance(lr_item_set_.begin(), pos);

      if (pos == lr_item_set_.end()) {
        lr_item_set_.push_back(gone.value());
      }
      if (curr_go.find(tok) != curr_go.end())
        throw runtime_error("Found shift-in <> shift-in conflict in: " +
                            tok.GetTokName());
#ifndef NDEBUG
      spdlog::debug("GO[ {} ; {} ] = {}", i, tok.ToString(), new_id);
#endif
      curr_go.insert({tok, new_id});
    };

    for_each(p_grammar->GetNonTerminators().cbegin(),
             p_grammar->GetNonTerminators().cend(), upd_f);
    for_each(p_grammar->GetTerminators().cbegin(),
             p_grammar->GetTerminators().cend(), upd_f);
  }
#ifndef NDEBUG
  stringstream ss;
  for (int i = 0; i < lr_item_set_.size(); ++i) {
    ss << "Item " << i << ":" << endl;
    for (const auto &lri : lr_item_set_[i]) {
      ss << "- " << lri.GetTokens().front() << " -> ";
      for (size_t j = 1; j <= lri.GetCurrentPosition(); ++j) {
        ss << lri.GetTokens()[j] << ", ";
      }
      ss << "[[^]]";
      for (size_t j = 1 + lri.GetCurrentPosition(); j < lri.GetTokens().size();
           ++j) {
        ss << lri.GetTokens()[j] << ", ";
      }
      ss << " [";
      copy(lri.GetLookAhead().begin(), lri.GetLookAhead().end(),
           ostream_iterator<Token>(ss, ", "));
      ss << "] " << endl;
    }
  }
  spdlog::debug("LRItem Set is as follow:\n{}\n----------", ss.str());
#endif
  FUNC_END_INFO;
}

Lr1::TokenSet Lr1::GetFirst(vector<Token>::const_iterator first,
                            vector<Token>::const_iterator last) const {
  if (first == last)
    return {p_grammar->GetEpsilonToken()};
  auto tok = *first;
  if (tok.GetTokenType() == Token::Type::kEpsilon)
    return {p_grammar->GetEpsilonToken()};

  auto s = first_set_.at(tok);
  if (s.find(p_grammar->GetEpsilonToken()) != s.end()) {
    // 当前 First set 有 Epsilon
    s.merge(GetFirst(first + 1, last));
  }
  return s;
}

unordered_set<LRItem, LRItem::Hash> Lr1::Lr1Closure(LRItemSet lrs) const {
  bool changed = true;
  while (changed) {
    changed = false;
    for (auto &lri : lrs) {
      auto next_tok = lri.Next();

      if (!next_tok.has_value())
        continue;

      if (next_tok->GetTokenType() != Token::Type::kNonTerminator)
        continue;

      // 找到可以扩张的production id
      const auto &related_prod =
          p_grammar->GetTokProdIdMap().at(next_tok.value());

      // 确定 look ahead 符号：
      auto rest = lri.Rest();
      auto look_ahead = GetFirst(rest.cbegin() + 1, rest.cend());
      if (look_ahead.find(p_grammar->GetEpsilonToken()) != look_ahead.end()) {
        look_ahead.erase(p_grammar->GetEpsilonToken());
        // epsilon in look_ahead.
        auto t = lri.GetLookAhead();
        look_ahead.merge(t);
      }

      for (auto id : related_prod) {
        LRItem deferred(p_grammar->GetProductions()[id].GetTokens(), look_ahead,
                        0);
        if (lrs.find(deferred) == lrs.end()) {
          lrs.insert(deferred);
          changed = true;
        }
      }
    }
  }

  // Do merge:
  LRItemSet merged;
  for (auto &i : lrs) {
    auto it = find_if(merged.begin(), merged.end(), [&i](const LRItem &lri) {
      return lri.GetTokens() == i.GetTokens() &&
             lri.GetCurrentPosition() == i.GetCurrentPosition();
    });

    if (it == merged.end()) {
      merged.insert(i);
    } else {
      auto las = it->GetLookAhead();
      merged.erase(it);
      las.merge(unordered_set(i.GetLookAhead()));
      merged.emplace(i.GetTokens(), las);
    }
  }

  return merged;
}

void Lr1::GenTable() {
  FUNC_START_INFO;
  lr_table_.Reset();
  lr_table_ = ParsingTable((int)lr_item_set_.size());
  auto aug_terminators = p_grammar->GetTerminators();
  aug_terminators.push_back(p_grammar->GetEpsilonToken());

  for (IdType i = 0; i < item_go_map_.size(); ++i) {
    auto &curr_lrs = lr_item_set_[i];

    // 对每一个状态，构建 Action 和 Goto
    // 1. GOTO
    for (const auto &tok : p_grammar->GetNonTerminators()) {
      auto f = item_go_map_[i].find(tok);
      if (f != item_go_map_[i].end()) {
        lr_table_.PutGoto(i, tok, f->second);
      }
    }

    // 2. Action: 可能有 shift-in <> reduce 冲突，需要解决
    // 当前的 Item Set
    for (const auto &tok : aug_terminators) {
      bool is_accept = false;
      if (tok == p_grammar->GetEpsilonToken()) {
        auto it =
            find_if(curr_lrs.begin(), curr_lrs.end(), [this](const LRItem &v) {
              return v.GetTokens() ==
                         vector<Token>{p_grammar->GetAugmentedToken(),
                                       p_grammar->GetEntryToken()} &&
                     v.CanReduce();
            });
        if (it != curr_lrs.end()) {
          lr_table_.PutAction(i, p_grammar->GetEndingToken(),
                              {.action = ParsingTable::kAccept});
          is_accept = true;
        }
      }
      if (is_accept)
        continue;

      auto f = item_go_map_[i].find(tok);
      ParsingTable::CellTp shift_in{.action =
                                        ParsingTable::AutomataAction::kEmpty};
      if (f != item_go_map_[i].end()) {
        // 如果可以shift-in
        shift_in = {.action = ParsingTable::AutomataAction::kShiftIn,
                    .id = f->second,
                    .cause = DeferGotoCause(i, f->second, tok)};
      }

      ParsingTable::CellTp reduce{.action =
                                      ParsingTable::AutomataAction::kEmpty};

      for (auto &lri : curr_lrs) {
        if (lri.CanReduce() &&
            lri.GetLookAhead().find(tok) != lri.GetLookAhead().end()) {
          auto prod_id = p_grammar->FindProd(lri.GetTokens());

          if (!prod_id.has_value()) {
            // 没找到 -> 抛出一个异常
            stringstream ss;
            copy(lri.GetTokens().cbegin(), lri.GetTokens().cend(),
                 ostream_iterator<Token>(ss, ", "));
            throw runtime_error(
                "LRItem with token not in production list found:\n\t" +
                ss.str());
          }

          auto pid = prod_id.value();
          if (reduce.action != ParsingTable::AutomataAction::kEmpty) {
            // 已经赋值
            spdlog::info(
                "Found Reduce <> Reduce conflict:\n\t{}: \n- with\n{}: {}", pid,
                p_grammar->GetProductions()[pid].ToString(), reduce.id,
                p_grammar->GetProductions()[reduce.id].ToString());
            if (pid < reduce.id) {
              reduce.id = pid;
              spdlog::info("Replace!");
            } else {
              spdlog::info("Do nothing!");
            }
          }

          reduce = ParsingTable::CellTp{
              .action = ParsingTable::AutomataAction::kReduce,
              .id = prod_id.value(),
          };
        }
      }

      if (shift_in.action == ParsingTable::AutomataAction::kEmpty &&
          reduce.action == ParsingTable::AutomataAction::kEmpty) {
        lr_table_.PutAction(i, tok, {.action = ParsingTable::kError});
      } else if (shift_in.action == ParsingTable::AutomataAction::kEmpty &&
                 reduce.action == ParsingTable::AutomataAction::kReduce) {
        lr_table_.PutAction(i, tok, reduce);
      } else if (shift_in.action == ParsingTable::AutomataAction::kShiftIn &&
                 reduce.action == ParsingTable::AutomataAction::kEmpty) {
        lr_table_.PutAction(i, tok, shift_in);
      } else /* conflict */ {
        // 生成提示信息
        stringstream ss;
        ss << "In state " << i << endl
           << "Causing Production:\nShiftIn:" << endl;
        for_each(shift_in.cause.begin(), shift_in.cause.end(),
                 [&ss, this](const auto &v) {
                   ss << "\t" << v << ": " << p_grammar->GetProductions()[v]
                      << endl;
                 });
        ss << "Reduce:" << endl
           << "\t" << reduce.id << ": "
           << p_grammar->GetProductions()[reduce.id] << endl;
        spdlog::info("Found Shift-In <> Reduce Conflict!\n{}", ss.str());

        // 处理冲突：
        // 1. 用结合律分析
        if (all_of(shift_in.cause.cbegin(), shift_in.cause.cend(),
                   [this, &reduce, &tok](const IdType &shift_in_prod_id) {
                     const auto &prod =
                         p_grammar->GetProductions()[shift_in_prod_id];
                     const auto &tokens = prod.GetTokens();
                     if (std::find(tokens.begin(), tokens.end(), tok) ==
                             tokens.end() ||
                         tok.GetAttr() == Token::Attr::kNone) {
                       return false;
                     }
                     return true;
                   })) {
          // 可以通过结合律解决
          if (tok.GetAttr() == Token::Attr::kLeftAssociative) {
            spdlog::info("Reduce. because {} Has LeftAssociative.",
                         tok.ToString());
            lr_table_.PutAction(i, tok, reduce);
          } else {
            spdlog::info("Shift In. because {} Has RightAssociative.",
                         tok.ToString());
            lr_table_.PutAction(i, tok, shift_in);
          }
        }

        // 2. 用优先级分析
        else if (all_of(shift_in.cause.cbegin(), shift_in.cause.cend(),
                        [&reduce](const auto &v) { return reduce.id < v; })) {
          // 执行reduce
          spdlog::info("Reduce. because of prio");
          lr_table_.PutAction(i, tok, reduce);
        } else if (all_of(shift_in.cause.cbegin(), shift_in.cause.cend(),
                          [&reduce](const auto &v) { return reduce.id > v; })) {
          // 执行 shift in
          spdlog::info("ShiftIn. because of prio");
          lr_table_.PutAction(i, tok, shift_in);
        } else {
          stringstream ss;
          for_each(shift_in.cause.begin(), shift_in.cause.end(),
                   [&ss, this](const auto &v) {
                     ss << p_grammar->GetProductions()[v] << endl;
                   });
          spdlog::error(
              "Cannot Decide shift-in or reduce:\nShift In:\n{}\nReduce:\n{}",
              ss.str(), p_grammar->GetProductions()[reduce.id].ToString());
          throw runtime_error("Cannot Decide when generating LR Table!");
        }
      }
    }
  }
  lr_table_.SetAugmentedToken(p_grammar->GetAugmentedToken());
  lr_table_.SetEndingToken(p_grammar->GetEndingToken());
  lr_table_.SetEntryToken(p_grammar->GetEntryToken());
  lr_table_.SetEpsilonToken(p_grammar->GetEpsilonToken());
  lr_table_.SetProductions((p_grammar->GetProductions()));
  FUNC_END_INFO;
}

vector<IdType> Lr1::DeferGotoCause(IdType lhs, IdType rhs, const Token &tok) {
  if (lhs >= lr_item_set_.size() || rhs >= lr_item_set_.size())
    throw runtime_error("Index Out of Range!");

  set<IdType> retval;

  for (const auto &k : lr_item_set_[lhs]) {
    auto opt_next_tok = k.Defer(tok);

    if (!opt_next_tok.has_value())
      continue;

    auto next_lri = opt_next_tok.value();

    if (lr_item_set_[rhs].find(next_lri) ==
        lr_item_set_[rhs].end()) // lhs -[tok]-> rhs 不成立
      continue;

    // 找到对应production
    auto opt_pid = p_grammar->FindProd(k.GetTokens());
    if (!opt_pid.has_value()) {
      // 没找到 -> 抛出一个异常
      stringstream ss;
      copy(k.GetTokens().cbegin(), k.GetTokens().cend(),
           ostream_iterator<Token>(ss, ", "));
      throw runtime_error(
          "LRItem with token not in production list found:\n\t" + ss.str());
    }
    IdType prod_id = opt_pid.value();
    retval.emplace(prod_id);
  }
  return {retval.begin(), retval.end()};
}
} // namespace sly::core::grammar
