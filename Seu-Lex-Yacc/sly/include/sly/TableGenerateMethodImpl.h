//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_TABLEGENERATEMETHODIMPL_H
#define SEULEXYACC_TABLEGENERATEMETHODIMPL_H
#include "def.h"
#include "TableGenerateMethod.h"
#include "ContextFreeGrammar.h"

namespace sly::core::grammar {

class Lr1: public TableGenerateMethod{
  using TokenSet = unordered_set<Token, Token::Hash>;

 public:
  void Defer(const ContextFreeGrammar &cfg) override;
 
 private:
  
  /**
   * 计算 First 集
   */
  void GenFirst();
  
  vector<IdType> DeferGotoCause(IdType lhs, IdType rhs, const Token &tok);
  
  
  /**
   * 计算 Follow 集
   */
  void GenFollow();
  
  /**
   * 计算 token list 的 first 集合
   * @param first
   * @param last
   * @return
   */
  TokenSet GetFirst(vector<Token>::const_iterator first, vector<Token>::const_iterator last) const;
  
  
  /**
   * 计算 LR-项集 和 GO 表
   * @param method
   */
  void GenItemGo();
  
  void GenTable();
  
  unordered_set<LRItem, LRItem::Hash> Lr1Closure(LRItemSet lrs) const;
  
  optional<unordered_set<LRItem, LRItem::Hash>> Lr1GotoFunc(const LRItemSet &lrs, const Token &tok) const;
  
  vector<unordered_map<Token, IdType, Token::Hash>> item_go_map_;
  
  vector<LRItemSet> lr_item_set_;
  
  unordered_map<Token, TokenSet, Token::Hash> first_set_;
  
  unordered_map<Token, TokenSet, Token::Hash> follow_set_;
  
};

}
#endif //SEULEXYACC_TABLEGENERATEMETHODIMPL_H
