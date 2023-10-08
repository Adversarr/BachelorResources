//
// Created by Yang Jerry on 2022/3/30.
//

#include <algorithm>
#include <array>
#include <iterator>
#include <queue>
#include <sly/FaModel.h>
#include <sly/TableGenerateMethod.h>
#include <sly/utils.h>
#include <utility>
#include <vector>
namespace sly::core::lexical {

NfaModel::NfaModel(optional<char> opt_c)
    : states_{Decline, Accept}, transition_(2), entries_{0} {
  char c = opt_c.value_or(EPSILON);
  transition_[0].insert({c, {1}});
  charset_.insert(c);
}

set<int> NfaModel::Defer(const set<int> &current_state,
                         optional<char> opt_c) const {

  set<int> result;
  char c = opt_c.value_or(EPSILON);
  for (auto state_i : GetEpsilonClosure(current_state)) {
    // 推导state_i状态下经过c的结果：
    const auto &trans_i = transition_[state_i];
    auto deferred_from_i = trans_i.find(c);
    if (trans_i.end() != deferred_from_i) {
      // 当前状态可以接受 c
      result.merge(set(deferred_from_i->second));
    }
  }

  // 计算 epsilon closure
  return GetEpsilonClosure(result);
}

set<int> NfaModel::GetEntry() const { return entries_; }

NfaModel NfaModel::Cascade(const NfaModel &another) const {
  set<char> new_cs;
  new_cs.insert(EPSILON);
  decltype(entries_) new_entries(entries_);
  decltype(states_) new_states(states_.size(), Decline);
  decltype(transition_) new_transition(transition_);
  int another_bias = (int)states_.size();

  // 拷贝 charset
  std::set_union(charset_.begin(), charset_.end(), another.charset_.begin(),
                 another.charset_.end(), inserter(new_cs, new_cs.end()));

  // 拷贝 states: [s.begin() ... end() a.s.begin() .. end()]
  for (auto s : another.states_) {
    new_states.push_back(s);
  }
  // 拷贝 transition:
  for (int i = 0; i < another.states_.size(); ++i) {
    // 对应 state 在 new_states 中的位置
    auto s_with_bias = another_bias + i;
    new_transition.push_back(map<char, set<int>>());
    auto &s_with_bias_transition = new_transition[s_with_bias];
    for (const auto &tr : another.transition_[i]) {
      set<int> updated;
      for (const auto &v : tr.second) {
        updated.insert(v + another_bias);
      }
      s_with_bias_transition.insert({tr.first, move(updated)});
    }
  }

  // 得到映射后的初态集合
  auto connection =
      utils::fmap<int>(another.entries_, [another_bias](const int &p) {
        return another_bias + p;
      });

  for (auto i : GetAcceptState()) {
    auto tr = new_transition[i].find(EPSILON);
    if (tr == new_transition[i].end())
      new_transition[i].insert(
          {EPSILON, set<int>(connection.begin(), connection.end())});
    else
      (tr->second).insert(connection.begin(), connection.end());
  }

  return NfaModel(move(new_cs), move(new_entries), move(new_states),
                  move(new_transition));
}

NfaModel::NfaModel(set<char> &&charset, set<int> &&entries,
                   vector<AutomataState> &&states,
                   vector<map<char, set<int>>> &&transition)
    : charset_(charset), entries_(entries), states_(states),
      transition_(transition) {
  // all attributes copied! do nothing.
}

vector<int> NfaModel::GetAcceptState() const {
  vector<int> result;
  for (auto i = 0; i < states_.size(); ++i) {
    if (states_[i])
      result.push_back(i);
  }
  return result;
}

NfaModel NfaModel::ToClosure() const {
  int entry_id = (int)states_.size(), accept_id = (int)states_.size() + 1;
  auto new_cs = charset_;
  new_cs.insert(EPSILON);
  decltype(entries_) new_entries{entry_id};
  decltype(states_) new_states(states_.size(), Decline);
  auto new_transition = transition_;
  new_states.push_back(Decline);
  new_states.push_back(Accept);
  // 入口节点
  new_transition.emplace_back(map<char, set<int>>{{EPSILON, {accept_id}}});
  // Accept 节点
  auto e = GetEntry();
  new_transition.emplace_back(
      map<char, set<int>>{{EPSILON, set(e.begin(), e.end())}});
  // 设置原有 Accept AutomataState 到入口的 epsilon 弧
  for (auto i : GetAcceptState()) {
    auto i_eps_tran = new_transition[i].find(EPSILON);
    if (i_eps_tran != new_transition[i].end()) {
      i_eps_tran->second.insert(entry_id);
    } else {
      new_transition[i].insert({EPSILON, {entry_id}});
    }
  }

  return NfaModel(move(new_cs), move(new_entries), move(new_states),
                  move(new_transition));
}

NfaModel NfaModel::Combine(const NfaModel &another) const {
  int entry_id = (int)(states_.size() + another.states_.size()),
      accept_id = entry_id + 1, bias = (int)states_.size();
  decltype(charset_) new_cs = charset_;
  decltype(entries_) new_entries{entry_id};
  decltype(states_) new_states(states_.size() + another.states_.size(),
                               Decline);
  decltype(transition_) new_transition(transition_);

  new_cs.insert(EPSILON);

  // 拷贝 charset:
  new_cs.merge(set(another.charset_));
  // 拷贝 transition:
  for (int i = 0; i < another.states_.size(); ++i) {
    // 对应 state 在 new_states 中的位置
    auto s_with_bias = bias + i;
    new_transition.push_back(map<char, set<int>>());
    auto &s_with_bias_transition = new_transition[s_with_bias];
    for (const auto &tr : another.transition_[i]) {
      set<int> updated;
      for (const auto &v : tr.second) {
        updated.insert(v + bias);
      }
      s_with_bias_transition.insert({tr.first, move(updated)});
    }
  }

  // 增加新的状态
  new_states.push_back(Decline);
  new_states.push_back(Accept);
  // 设置新的入口
  auto original_entries = GetEntry();
  transform(another.entries_.begin(), another.entries_.end(),
            inserter(original_entries, original_entries.end()),
            [bias](const auto &v) { return v + bias; });
  new_transition.push_back(
      {{EPSILON, set(original_entries.begin(), original_entries.end())}});
  new_transition.push_back({});

  // 设置新的出口
  auto original_accept = GetAcceptState();
  for (auto a : another.GetAcceptState()) {
    original_accept.push_back(a + bias);
  }
  for (auto i : original_accept) {
    auto f = new_transition[i].find(EPSILON);
    if (f == new_transition[i].end()) // 没有 epsilon 出边
    {
      new_transition[i].insert({EPSILON, {accept_id}});
    } else // 有 epsilon 出边
    {
      f->second.insert(accept_id);
    }
  }

  return NfaModel(move(new_cs), move(new_entries), move(new_states),
                  move(new_transition));
}

set<int> NfaModel::GetEpsilonClosure(const set<int> &s) const {
  return utils::fixed_point<int>(s, [this](const int &i) {
    auto tr = this->transition_[i].find(EPSILON);
    if (tr != transition_[i].end())
      return tr->second;
    return set<int>{};
  });
}

const set<char> &NfaModel::GetCharset() const { return charset_; }

NfaModel::NfaModel(set<char> accept)
    : charset_(std::move(accept)), states_{Decline, Accept},
      transition_(2), entries_{0} {
  for (const auto &c : charset_) {
    transition_[0].insert({c, {1}});
  }
}

DfaModel::DfaModel(NfaModel &nfa) : charset_(nfa.GetCharset()) {
  charset_.erase(EPSILON);
  vector<set<int>> subsets{nfa.GetEpsilonClosure(nfa.GetEntry())};
  int curr = 0;

  auto nfa_accept_states = nfa.GetAcceptState();
  auto can_accept = [&nfa_accept_states](const set<int> &s) {
    vector<int> temp;
    set_intersection(s.begin(), s.end(), nfa_accept_states.begin(),
                     nfa_accept_states.end(), back_inserter(temp));
    return !temp.empty();
  };
  while (curr < (int)subsets.size()) {
    states_.push_back(can_accept(subsets[curr]));
    transition_.push_back({});
    for (auto c : charset_) {
      if (c == EPSILON) // EPSILON edge
        continue;
      auto deferred = nfa.Defer(subsets[curr], {c});
      if (deferred.empty()) // empty emplace
        continue;

      auto deferred_iter = find(subsets.begin(), subsets.end(), deferred);
      int deferred_id = (int)distance(subsets.begin(), deferred_iter);
      if (deferred_iter == subsets.end()) // not found.
      {
        subsets.push_back(deferred);
      }
      transition_.back().insert({c, deferred_id});
    }
    curr += 1;
  }
}

const set<char> &DfaModel::GetCharset() const { return charset_; }

const vector<AutomataState> &DfaModel::GetStates() const { return states_; }

const vector<map<char, int>> &DfaModel::GetTransition() const {
  return transition_;
}

optional<int> DfaModel::Defer(int sid, char c) const {
  if (sid < 0 || sid >= states_.size())
    return {};

  auto deferred = transition_[sid].find(c);
  if (deferred == transition_[sid].end())
    return {};
  return deferred->second;
}

DfaModel::CStyleTable DfaModel::ToCTable() const {
  CStyleTable table;
  for (auto &trans : transition_) {
    decltype(CStyleTable::transition_)::value_type tr_item(128, -1);
    fill(tr_item.begin(), tr_item.end(), -1);
    for (auto [k, v] : trans) {
      tr_item[k] = v;
    }
    table.transition_.emplace_back(tr_item);
  }
  copy(states_.begin(), states_.end(), back_inserter(table.can_accept_));
  return move(table);
}

DfaController::DfaController(DfaModel model)
    : p_dfa_(make_shared<DfaModel>(move(model))), current_state_(0) {}

DfaController::DfaController(shared_ptr<DfaModel> p_dfa,
                             optional<int> current_state)
    : p_dfa_(std::move(p_dfa)), current_state_(current_state) {}

AutomataState DfaController::CanAccept() const {
  if (current_state_.has_value())
    return p_dfa_->GetStates()[current_state_.value()];
  else
    return Decline;
}

DfaController DfaController::Defer(char c) const {
  if (current_state_.has_value())
    return {p_dfa_, p_dfa_->Defer(current_state_.value(), c)};
  else
    return *this;
}

NfaModel operator+(const NfaModel &na, const NfaModel &nb) {
  return na.Combine(nb);
}

NfaModel operator*(const NfaModel &na, const NfaModel &nb) {
  return na.Cascade(nb);
}

NfaModel operator++(const NfaModel &na) { return na.ToClosure(); }

pair<vector<vector<int>>, vector<int>> DfaModel::Merge(const std::vector<DfaModel> &dfa_list) {
  vector<vector<int>> transitions;
  vector<int> accept;
  // treat these dfa as nfa and merge
  // states[i] == id >=  0 表示第 i 个 dfa 状态为 id
  //              id == -1 表示第 i 个 dfa 已经退出
  vector<vector<int>> states;
  states.emplace_back();
  for (const auto & dfa: dfa_list) {
    states.front().push_back(dfa.entry_);
  }
  
  auto determine_can_accept = [&dfa_list](const vector<int> &state) {
    for (int i = 0; i < dfa_list.size(); ++i) {
      if (state[i] < 0 || state[i] >= dfa_list[i].states_.size())
        continue;
      if (dfa_list[i].states_[state[i]]) {
        return i;
      }
    }
    return -1;
  };
  // 扩展状态直到收敛
  for (int i = 0; i < states.size(); ++i) {
    // 获取当前状态
    vector<int> current = states[i];
    spdlog::debug("state {}", i);
    // 在返回值中添加状态是否可以作为结束的标记
    accept.push_back(determine_can_accept(current));
    vector<int> tran(128, -1);
    // 对所有转义字符执行转移
    set<char> charset;
    for(int i = 0; i < dfa_list.size(); ++i) {
      if (current[i] != -1) {
        for (const auto& [k, v]: dfa_list[i].GetTransition()[current[i]]) {
          charset.emplace(k);
        }
      }
    }
    for (auto c: charset) {
      vector<int> transition_target_state;
      for (int i = 0; i < dfa_list.size(); ++i) {
        const auto& dfa = dfa_list[i];
        const auto& state = current[i];
        if (state == -1) {
          transition_target_state.emplace_back(-1);
        } else {
          if (const auto &it = dfa.transition_[state].find(c);
              it != dfa.transition_[state].end()) {
            transition_target_state.emplace_back(it->second);
          } else {
            transition_target_state.emplace_back(-1);
          }
        }
      }
      // 检查状态
      if (auto it = find(cbegin(states), cend(states), transition_target_state);
          it != states.end()) {
        // 说明转移到了 id 处
        auto id = distance(states.cbegin(), it);
        tran[c] = id;
      } else {
        // 新状态
        auto id = states.size();
        states.emplace_back(move(transition_target_state));
        tran[c] = id;
      }
    }
    transitions.emplace_back(move(tran));
  }
  return {transitions, accept};
}

} // namespace sly::core::lexical