//
// Created by Yang Jerry on 2022/3/30.
//

#include <sly/ContextFreeGrammar.h>
#include <sly/utils.h>
#include <sly/Token.h>
#include <sly/Production.h>
#include <sly/Action.h>
#include <sstream>

using namespace sly::utils;


namespace sly::core::grammar{

const ParsingTable &ContextFreeGrammar::GetLrTable() const {
  return lr_table_;
}

const vector<Production> &ContextFreeGrammar::GetProductions() const {
  return productions_;
}

void ContextFreeGrammar::SetProductions(const vector<Production> &productions) {
  ContextFreeGrammar::productions_ = productions;
}

const Token &ContextFreeGrammar::GetEntryToken() const {
  return entry_token_;
}

void ContextFreeGrammar::SetEntryToken(const Token &entry_token) {
  ContextFreeGrammar::entry_token_ = entry_token;
}

const Token &ContextFreeGrammar::GetEndingToken() const {
  return ending_token_;
}

void ContextFreeGrammar::SetEndingToken(const Token &ending_token) {
  ContextFreeGrammar::ending_token_ = ending_token;
}

void ContextFreeGrammar::CheckHealthAndPrepare() {
  FUNC_START_INFO;
  Reset();
  // 0. 增广文法
  epsilon_token_ = Token();
  augmented_token_ = Token::NonTerminator("#LR augmented#");
  productions_.insert(productions_.begin(),
                      Production(augmented_token_)(entry_token_));
  
  // 1. 计算所有非终结符/终结符
  non_terminators_.clear();
  terminators_.clear();
  terminators_.emplace_back(ending_token_);
  
  for (auto &prod: productions_) {
    // 所有产生式左部的都是非终结符。
    if (!prod.CheckHealth())
      throw runtime_error("Exist one broken production.");
    auto &lhs = prod.GetTokens().front();
    
    if (!PutNonTerminator(lhs))
      throw runtime_error("Found not non-term on lhs in prod <lhs: " + lhs.GetTokName() + ">");
  }
  
  for (auto &prod: productions_) {
    for (auto &t: prod.GetTokens()) {
      switch (t.GetTokenType()) {
        case Token::Type::kEpsilon:
          epsilon_token_ = t;
          break;
        case Token::Type::kTerminator:
          PutTerminator(t);
          break;
        default:
          break;
      }
    }
  }
  // 3. 检查一致性
  if (ending_token_.GetTokenType() != Token::Type::kTerminator)
    throw runtime_error("Ending token is not a terminator!");
  if (entry_token_.GetTokenType() != Token::Type::kNonTerminator)
    throw runtime_error("Entry token is not a non-terminator!");
  
  for (auto &prod: productions_) {
    for (auto &tok: prod.GetTokens()) {
      switch (tok.GetTokenType()) {
        case Token::Type::kEpsilon:
          if (!(tok == epsilon_token_))
            throw runtime_error("Found Epsilon in token-list.");
          break;
        case Token::Type::kTerminator:
          if (find(terminators_.begin(), terminators_.end(), tok) == terminators_.end())
            throw runtime_error("Cannot find terminator. <" + tok.GetTokName() + ">");
          break;
        case Token::Type::kNonTerminator:
          if (tok_prod_id_map_.find(tok) == tok_prod_id_map_.end())
            throw runtime_error("Cannot find non-term. <" + tok.GetTokName() + ">");
          break;
        default:
          throw runtime_error("There exist an empty Token in grammar");
      }
    }
  }
  // 4. 计算map
  for (IdType i = 0; i < productions_.size(); ++i) {
    auto &prod = productions_[i];
    auto &lhs = prod.GetTokens().front();
    tok_prod_id_map_[lhs].push_back(i);
  }
  
  // 5. 确保没有重复产生式
  for (const auto &pi: productions_) {
    int count = 0;
    for (const auto &pj: productions_) {
      if (pi == pj) count += 1;
    }
    if (count > 1)
      throw runtime_error("Found duplicated production.");
  }
  FUNC_END_INFO;
}


void ContextFreeGrammar::Compile(TableGenerateMethod& method) {
  CheckHealthAndPrepare();
  method.Defer(*this);
  lr_table_ = method.GetParsingTable();
}

void ContextFreeGrammar::Reset() {
  non_terminators_.clear();
  terminators_.clear();
  lr_table_.Reset();
}

ContextFreeGrammar::ContextFreeGrammar(vector<Production> prod_list, Token entry, Token ending) :
  productions_(std::move(prod_list)),
  entry_token_(std::move(entry)),
  ending_token_(std::move(ending)) {
  
}

bool ContextFreeGrammar::PutTerminator(const Token &tok) {
  if (tok.GetTokenType() != Token::Type::kTerminator &&
      tok.GetTokenType() != Token::Type::kEpsilon)
    return false;
  auto it = find(terminators_.begin(), terminators_.end(), tok);
  if (it == terminators_.end())
    terminators_.push_back(tok);
  return true;
}

bool ContextFreeGrammar::PutNonTerminator(const Token &tok) {
  if (tok.GetTokenType() != Token::Type::kNonTerminator)
    return false;
  auto it = find(non_terminators_.begin(), non_terminators_.end(), tok);
  if (it == non_terminators_.end()) {
    non_terminators_.push_back(tok);
    tok_prod_id_map_.insert({tok, {}});
  }
  return true;
}

optional<IdType> ContextFreeGrammar::FindProd(const Production::TokenVec &token_vec) const {
  auto it = find_if(
    productions_.begin(), productions_.end(),
    [&token_vec](const Production &prod) { return prod.GetTokens() == token_vec; });
  if (it == productions_.end())
    return {};
  
  return distance(productions_.begin(), it);
}

const vector<Token> &ContextFreeGrammar::GetNonTerminators() const {
  return non_terminators_;
}

const vector<Token> &ContextFreeGrammar::GetTerminators() const {
  return terminators_;
}

const unordered_map<Token, vector<IdType>, Token::Hash> &ContextFreeGrammar::GetTokProdIdMap() const {
  return tok_prod_id_map_;
}

const Token &ContextFreeGrammar::GetAugmentedToken() const {
  return augmented_token_;
}

const Token &ContextFreeGrammar::GetEpsilonToken() const {
  return epsilon_token_;
}


std::size_t LRItem::Hash::operator()(const LRItem &k) const {
  size_t hv = 0;
  for (const auto &tok: k.GetTokens()) {
    hv = hash_combine(hv, Token::Hash{}(tok));
  }
  for (const auto &tok: k.GetLookAhead()) {
    hv = hash_combine(hv, Token::Hash{}(tok));
  }
  return hv;
}

bool LRItem::operator==(const LRItem &rhs) const {
  return tokens_ == rhs.tokens_ && look_ahead_ == rhs.look_ahead_ && current_position_ == rhs.current_position_;
}

LRItem::LRItem(Production::TokenVec tos, Production::TokenSet las, size_t cur_pos) :
  tokens_(std::move(tos)), look_ahead_(move(las)), current_position_(cur_pos) {
  for (const auto &t: las) {
    if (t.GetTokenType() != Token::Type::kTerminator)
      throw runtime_error("Found non-term in Look Ahead!");
  }
}

optional<LRItem> LRItem::Defer(const Token &tok) const {
  if (current_position_ + 1 >= tokens_.size())
    return {};
  
  if (!(tokens_[current_position_ + 1] == tok))
    return {};
  
  return make_optional(move(LRItem(tokens_, look_ahead_, current_position_ + 1)));
}

const Production::TokenVec &LRItem::GetTokens() const {
  return tokens_;
}

const Production::TokenSet &LRItem::GetLookAhead() const {
  return look_ahead_;
}

size_t LRItem::GetCurrentPosition() const {
  return current_position_;
}

optional<Token> LRItem::Next() const {
  if (current_position_ + 1 < tokens_.size())
    return tokens_[current_position_ + 1];
  
  return {};
}

bool LRItem::CanReduce() const {
  return current_position_ + 1 == tokens_.size();
}

Production::TokenVec LRItem::Rest() const {
  if (CanReduce())
    return {};
  else
    return {tokens_.begin() + static_cast<long>(current_position_ + 1),
            tokens_.end()};
}

void LRItem::SetLookAhead(const Production::TokenSet &las) {
  look_ahead_ = las;
}

}
