//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_PRODUCTION_H
#define SEULEXYACC_PRODUCTION_H

#include "def.h"
#include <unordered_set>
#include <vector>
#include "Token.h"
#include "Action.h"

namespace sly::core::type
{

/**
 * 含有 Action 和 Token 的产生式
 */
class Production {
 public:
  
  using TokenVec = std::vector<Token>;
  
  using TokenSet = std::unordered_set<Token, Token::Hash>;
  
  bool CheckHealth() const;
  
  bool IsEpsilon() const;
  
  Production(std::vector<Token> tokens, std::vector<Action> actions);
  
  Production();
  
  explicit Production(Token start);
  
  explicit Production(Token start, Action act);
  
  Production operator()(Token next_token) const;
  
  Production operator()(Token next_token, Action next_action) const;
  
  bool operator==(const Production &rhs) const;
  
  vector<Token> &GetTokens();

  const vector<Token> &GetTokens() const;
 
  const vector<Action> &GetActions() const;
  string ToString() const;
 private:
  TokenVec tokens_;
  
  std::vector<Action> actions_;
};

ostream &operator<<(ostream &os, const Production &prod);

}

#endif //SEULEXYACC_PRODUCTION_H
