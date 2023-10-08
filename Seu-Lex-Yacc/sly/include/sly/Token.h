//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_TOKEN_H
#define SEULEXYACC_TOKEN_H
#include "def.h"
#include <string>

using namespace std;

namespace sly::core::type {
/**
 * (LR 自动机中) Token 类
 */
class Token {
public:
  enum class Type { kTerminator, kNonTerminator, kEpsilon };

  enum class Attr { kLeftAssociative, kRightAssociative, kNone };

  // Token hash
  struct Hash {
    std::size_t operator()(const Token &k) const;
  };

  bool operator==(const Token &another) const;
  bool operator!=(const Token &another) const;

  bool IsTerminator() const;

  const string &GetTokName() const;

  Type GetTokenType() const;

  Token();

  static Token NonTerminator(string tok_name, IdType tid,
                             Attr attr = Attr::kNone);

  static Token Terminator(string tok_name, IdType tid,
                          Attr attr = Attr::kNone);

  static Token NonTerminator(string tok_name, Attr attr = Attr::kNone);

  static Token Terminator(string tok_name, Attr attr = Attr::kNone);

  explicit Token(string tok_name, Type tok_type, IdType tid,
                 Attr attr = Attr::kNone);

public:
  IdType GetTid() const;

  Attr GetAttr() const;

  void SetAttr(Attr attribute);

  bool operator<(const Token &rhs) const;

  void PrintImpl(std::ostream &os) const;

  string ToString() const;

  size_t hash() const;

private:
  IdType tid_;

  Attr attr_;

  std::string name_;

  Type type_;
};

ostream &operator<<(ostream &os, const Token &tok);

ostream &operator<<(ostream &os, const Token::Attr &attr);

ostream &operator<<(ostream &os, const Token::Type &type);
} // namespace sly::core::type
#endif // SEULEXYACC_TOKEN_H
