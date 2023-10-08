//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_REGEX_H
#define SEULEXYACC_REGEX_H
#include "def.h"
#include "FaModel.h"
#include <memory>
#include <string>
#include <iostream>
namespace sly::core::lexical {

class RegEx {
 public:

  explicit RegEx(std::string expr);
  
  bool CanMatch(std::string str);
  
  void Compile();
  
  const DfaModel& GetDfaModel();

 private:

  std::string expr_;

  DfaModel dfa_model_;

  bool compiled = false;
};



}
#endif //SEULEXYACC_REGEX_H
