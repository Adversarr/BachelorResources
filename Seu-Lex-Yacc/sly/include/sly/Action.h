//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_ACTION_H
#define SEULEXYACC_ACTION_H

#include "def.h"
#include <vector>
#include <functional>
#include <optional>
#include <string>
#include <iostream>
namespace sly::core::type {
/**
 * LR 自动机中的 Action 类
 */
class Action {
 public:
  using ActionFType = std::function<void(std::vector<YYSTATE> &)>;
  
  void Modify(std::vector<TokenAttr> &tokens);
  
  Action();
  
  Action(ActionFType f);
  
  Action(ActionFType f, std::string impl);
  
  bool operator==(const Action &rhs) const;
  
  inline std::string GetImpl() const;

  std::string ToString() const;
 
 private:
  std::optional<ActionFType> opt_f_;
  
  std::string impl_;
};

std::ostream &operator<<(std::ostream &os, const Action &act);

std::string Action::GetImpl() const {
  return impl_;
}
}


#endif //SEULEXYACC_ACTION_H
