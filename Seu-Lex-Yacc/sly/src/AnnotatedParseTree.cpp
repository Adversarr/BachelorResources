//
// Created by Yang Jerry on 2022/3/30.
//

#include <sly/AnnotatedParseTree.h>

#include <iomanip>
#include <sstream>
#include <utility>

namespace sly::core::type {

AnnotatedParseTree::AnnotatedParseTree(Token token, AttrDict attr): 
  is_annotated_(true), type_(Type::kTerminator),
  token_(std::move(token)), attrs_({std::move(attr)})
{
}

AnnotatedParseTree::AnnotatedParseTree(const Production& prod):
  is_annotated_(false), type_(Type::kNonTerminator), actions_(prod.GetActions()), token_(prod.GetTokens().front())
{
}


const vector<AttrDict> &sly::core::type::AnnotatedParseTree::GetRootAttributes() const {
  return attrs_;
}


void AnnotatedParseTree::Annotate(AnnotatedParseTree* p_father) {
  if (type_ == Type::kTerminator) { // leaf node, do nothing and return.
    return;
  }
  
  is_annotated_ = false;
  attrs_.clear();
  attrs_.emplace_back();
  for (int i = 1; i < actions_.size(); ++i) {
    auto p = sub_nodes_[i - 1];
    if (!(p->is_annotated_)) {
      p->Annotate(this);
    }
    if (!(p->is_annotated_)) {
      if (p_father == nullptr) {
        throw runtime_error("Cannot annotate.");
      }
      return;
    }
    attrs_.emplace_back(p->attrs_.front());
    actions_[i].Modify(attrs_);
  }
  actions_[0].Modify(attrs_);
  is_annotated_ = true;
}

void AnnotatedParseTree::PushBack(AnnotatedParseTree tree) {
  EmplaceBack(move(tree));
}

void AnnotatedParseTree::EmplaceBack(AnnotatedParseTree &&tree) {
  sub_nodes_.emplace_back(make_shared<AnnotatedParseTree>(tree));
}


void AnnotatedParseTree::EmplaceFront(AnnotatedParseTree &&tree) {
  sub_nodes_.emplace_front(make_shared<AnnotatedParseTree>(tree));
}

string AnnotatedParseTree::ToString() const {
  stringstream ss;
  Print(ss);
  return "AnnontatedParseTree{\n" + ss.str() + "}";
}

void AnnotatedParseTree::PrintForShort(ostream& oss, bool printAttr) const {
  Print_(oss, true, printAttr);
}

void AnnotatedParseTree::Print(ostream& oss, bool printAttr) const {
  Print_(oss, false, printAttr);
}

void AnnotatedParseTree::Print_(ostream &oss, bool forShort, bool printAttr, int depth, vector<bool> isLast) const {
  if (depth == 0) {
    oss << " ";
  }
  for (int i = 0; i < isLast.size(); i++) {
    if (i + 1 == isLast.size()) {
      oss << (isLast[i] ? " └ " : " ├ ");
    } else {
      oss << (isLast[i] ? "  " : " │");
    }
  }
  // print token name
  if (type_ == Type::kNonTerminator) {
    oss << "\033[35m" << token_.GetTokName() << "\033[0m";
  } else {
    oss << "\033[34m" << token_.GetTokName() << "\033[0m";
  }
  oss << " ";
  // print attributes
  if (type_ == Type::kNonTerminator) {
    if (printAttr) {
      oss << "[";
      if (!attrs_.empty()) {
        auto dict = attrs_[0].ToStrDict();
        for (const auto&[k, v]: dict) {
          if (typeid(v) == typeid(std::string)) {
            oss << k << ":" << sly::utils::escape(v) << " /";
          } else {
            oss << k << ":" << v << " /";
          }
        }
      }
      oss << "]";
    }
  } else {
    oss << "<line:" << attrs_[0].Get<int>("row") << ":" << attrs_[0].Get<int>("col") << ">";
    oss << " ";
    oss << "\"\033[33m" << sly::utils::escape(attrs_[0].Get<string>("lval")) << "\033[0m\"";
    if (printAttr) {
      oss << " [";
      if (!attrs_.empty()) {
        auto dict = attrs_[0].ToStrDict();
        for (const auto&[k, v]: dict) {
          if (k == "lval" || k == "row" || k == "col") {
            continue;
          }
          if (typeid(v) == typeid(std::string)) {
            oss << k << ":" << sly::utils::escape(v) << " /";
          } else {
            oss << k << ":" << v << " /";
          }
        }
      }
      oss << "]";
    }
  }
  // // print other attributes
  // if (type_ == Type::kNonTerminator) {
  //   oss << "\033[32m" << token_.GetTokName() << "\033[0m";
  // } else {
  //   oss << "\033[34m" << token_.GetTokName() << "\033[0m";
  // } 
  // oss << ">";
  oss << std::endl;
  isLast.emplace_back(false);
  if (type_ == Type::kNonTerminator) {
    // for (const auto &sub_node: sub_nodes_) {
    if (forShort && sub_nodes_.size() == 1) {
      SubNode sub_node = sub_nodes_[0];
      while (sub_node->type_ ==  Type::kNonTerminator && sub_node->sub_nodes_.size() == 1) {
        sub_node = sub_node->sub_nodes_[0];
      }
      isLast.back() = true;
      sub_node->Print_(oss, forShort, printAttr, depth + 1, isLast);
    } else {
      for (auto it = sub_nodes_.begin(); it != sub_nodes_.end(); it++) {
        if (it + 1 == sub_nodes_.end()) {
          isLast.back() = true;
        }
        (*it)->Print_(oss, forShort, printAttr, depth + 1, isLast);
      }
    }
  }
}

} // namespace sly::core::type
