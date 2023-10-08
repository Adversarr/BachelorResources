//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_ANNOTATEDPARSETREE_H
#define SEULEXYACC_ANNOTATEDPARSETREE_H


#include "def.h"
#include "Token.h"
#include "Production.h"
#include "AttrDict.h"
#include <memory>
#include <vector>
#include <deque>
#include <string>

using namespace std;

namespace sly::core::type {
class AnnotatedParseTree {
 public:
  enum class Type{
    kNonTerminator,
    kTerminator
  };
  
  using SubNode = std::shared_ptr<AnnotatedParseTree>;
  
  const vector<AttrDict> &GetRootAttributes() const;
  
  void EmplaceBack(AnnotatedParseTree&& tree);

  void EmplaceFront(AnnotatedParseTree&& tree);
  
  void PushBack(AnnotatedParseTree tree);
  
  void Annotate(AnnotatedParseTree* p_father = nullptr);
  
  AnnotatedParseTree(Token token, AttrDict attr);
  
  explicit AnnotatedParseTree(const Production& prod);
  
  void PrintForShort(ostream& oss, bool printAttr=true) const;

  void Print(ostream& oss, bool printAttr=true) const;

  string ToString() const;
  
 private:
  Type type_;
  
  Token token_;
  
  vector<AttrDict> attrs_;
  
  vector<Action> actions_;
  
  std::deque<SubNode> sub_nodes_;

  void Print_(ostream& oss, bool forShort=false, bool printAttr=true, int depth=0, vector<bool> isLast={}) const;
  
  bool is_annotated_; 
};
}

#endif //SEULEXYACC_ANNOTATEDPARSETREE_H
