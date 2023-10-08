
#ifndef SEULEXYACC_FILEANALYZER_H
#define SEULEXYACC_FILEANALYZER_H
#include "def.h"
#include "FaModel.h"
#include <memory>
#include <string>
#include <iostream>
namespace sly::core::lexical {


class PrefixRegExMatcher {
 public:

  explicit PrefixRegExMatcher(std::string expr);
  
  inline const std::size_t GetLength() const ;
  
  inline const DfaModel& GetDfaModel() const ;

 private:

  std::string expr_;
  std::string regex_expr_;

  DfaModel dfa_model_;

};

const std::size_t PrefixRegExMatcher::GetLength() const {
  return regex_expr_.length();
}

const DfaModel& PrefixRegExMatcher::GetDfaModel() const {
  return dfa_model_;
}


}
#endif //SEULEXYACC_FILEANALYZER_H
