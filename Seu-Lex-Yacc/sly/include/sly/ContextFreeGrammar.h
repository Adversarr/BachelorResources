//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_CONTEXTFREEGRAMMAR_H
#define SEULEXYACC_CONTEXTFREEGRAMMAR_H

#include "def.h"
#include "Token.h"
#include "Production.h"
#include "TableGenerateMethod.h"
#include <optional>
#include <unordered_set>
#include <unordered_map>

using namespace std;

namespace sly::core::grammar {
using namespace type;

class LRItem {
 public:
  
  explicit LRItem(Production::TokenVec tos,
                  Production::TokenSet las,
                  size_t cur_pos = 0);
  
  bool operator==(const LRItem &rhs) const;
  
  optional<LRItem> Defer(const Token &tok) const;
  
  const Production::TokenVec &GetTokens() const;
  
  const Production::TokenSet &GetLookAhead() const;
  
  void SetLookAhead(const Production::TokenSet &las);
  
  /**
   * 返回当前 look-ahead 标记位置
   * @return
   */
  size_t GetCurrentPosition() const;
  
  optional<Token> Next() const;
  
  bool CanReduce() const;
  
  Production::TokenVec Rest() const;
  
  struct Hash {
    std::size_t operator()(const LRItem &k) const;
  };
 
 private:
  
  Production::TokenVec tokens_;
  
  Production::TokenSet look_ahead_;
  
  size_t current_position_;
};

using LRItemSet = std::unordered_set<LRItem, LRItem::Hash>;


class ContextFreeGrammar {
 public:
  
  explicit ContextFreeGrammar(vector<Production> prod_list, Token entry, Token ending);
  
  
  /**
   * 编译文法
   * @param method
   */
  void Compile(TableGenerateMethod &method);
  
  void Reset();
 
  const vector<Production> &GetProductions() const;
  
  void SetProductions(const vector<Production> &productions);
  
  const Token &GetEntryToken() const;
  
  void SetEntryToken(const Token &entry_token);
  
  const Token &GetEndingToken() const;
  
  void SetEndingToken(const Token &ending_token);
  
  const ParsingTable &GetLrTable() const;
  
  /**
   * 查找production
   * @param token_vec
   * @return
   */
  optional<IdType> FindProd(const Production::TokenVec &token_vec) const;
 
 public:
  const unordered_map<Token, vector<IdType>, Token::Hash> &GetTokProdIdMap() const;
  
  const Token &GetAugmentedToken() const;
  
  const Token &GetEpsilonToken() const;
  
  const vector<Token> &GetNonTerminators() const;
  
  const vector<Token> &GetTerminators() const;
  
 private:
  
  /**
   * 一般规范性检查，准备辅助数据结构
   */
  void CheckHealthAndPrepare();
 
  
  /**
   * 添加终结符
   * @param tok
   * @return
   */
  bool PutTerminator(const Token &tok);
  
  
  /**
   * 添加非终结符
   * @param tok
   * @return
   */
  bool PutNonTerminator(const Token &tok);
 
 private:
  
  vector<Token> non_terminators_;
  
  vector<Token> terminators_;
  
  vector<Production> productions_;
  
  unordered_map<Token, vector<IdType>, Token::Hash> tok_prod_id_map_;
  
  Token entry_token_;
  
  Token augmented_token_;
  
  Token ending_token_;
  
  Token epsilon_token_;
  
  ParsingTable lr_table_;
};
}

#endif //SEULEXYACC_CONTEXTFREEGRAMMAR_H
