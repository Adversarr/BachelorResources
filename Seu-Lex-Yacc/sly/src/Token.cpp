//
// Created by Yang Jerry on 2022/3/30.
//

#include <sly/Token.h>
#include <sly/utils.h>
#include <cassert>
#include <sstream>

namespace sly::core::type {


std::size_t Token::Hash::operator()(const Token &k) const
{
  return sly::utils::hash(k.GetTokName(), k.GetTokenType());
}

bool Token::operator==(const Token &another) const
{
  return type_ == another.type_ &&
         name_ == another.name_;
}

bool Token::operator!=(const Token &another) const
{
  return !(type_ == another.type_ &&
           name_ == another.name_);
}

bool Token::IsTerminator() const
{
  return type_ == Type::kTerminator;
}

size_t Token::hash() const {
  return Token::Hash{}(*this);
}

Token::Token(string tok_name, Type tok_type, IdType tid, Attr attr) :
  name_(std::move(tok_name)), tid_(tid), type_(tok_type), attr_(attr)
{
}

Token Token::NonTerminator(string tok_name, IdType tid, Attr attr)
{
  return Token(std::move(tok_name), Type::kNonTerminator, tid, attr);
}

Token Token::Terminator(string tok_name, IdType tid, Attr attr)
{
  return Token(std::move(tok_name), Type::kTerminator, tid, attr);
}

Token Token::NonTerminator(string tok_name, Attr attr) {
  return Token(std::move(tok_name), Type::kNonTerminator, 0, attr);
}

Token Token::Terminator(string tok_name, Attr attr) {
  return Token(std::move(tok_name), Type::kTerminator, 0, attr);
}

Token::Token()
{
  type_ = Type::kEpsilon;
  attr_ = Attr::kNone;
  tid_ = 0;
}


const string &Token::GetTokName() const
{
  return name_;
}

Token::Type Token::GetTokenType() const
{
  return type_;
}

IdType Token::GetTid() const
{
  return tid_;
}

bool Token::operator<(const Token &rhs) const
{
  if (name_ < rhs.name_)
    return true;
  if (type_ < rhs.type_)
    return true;
  return false;
}

Token::Attr Token::GetAttr() const
{
  return attr_;
}

void Token::SetAttr(Token::Attr attribute)
{
  Token::attr_ = attribute;
}

string translate_to_raw_form(const string & origin) {
  string s;
  for (auto c: origin) {
    s.push_back(c);
    if (c == '\\') {
      s.push_back(c);
    }
  }
  return s;
}


ostream &operator<<(ostream &os, const Token &tok)
{
  switch (tok.GetTokenType())
  {
    case Token::Type::kNonTerminator:
      os << "N<\033[33m" + tok.GetTokName() + "\033[0m>";
      break;
    case Token::Type::kTerminator:
      os << "T<\033[33m" + tok.GetTokName() + "\033[0m>";
      break;
    case Token::Type::kEpsilon:
      os << "E< >";
      break;
  }
  return os;
}

ostream &operator<<(ostream &os, const Token::Attr& attr) {
  if (attr == Token::Attr::kLeftAssociative) {
    os << "sly::core::type::Token::Attr::kLeftAssociative";
  } else if (attr == Token::Attr::kRightAssociative) {
    os << "sly::core::type::Token::Attr::kRightAssociative";
  } else if (attr == Token::Attr::kNone) {
    os << "sly::core::type::Token::Attr::kNone";
  } else {
    spdlog::error("{}",(int) attr);
    exit(1);
  }
  return os;
}

ostream &operator<<(ostream &os, const Token::Type& type) {
  if (type == Token::Type::kTerminator) {
    os << "sly::core::type::Token::Type::kTerminator";
  } else if (type == Token::Type::kNonTerminator) {
    os << "sly::core::type::Token::Type::kNonTerminator";
  } else if (type == Token::Type::kEpsilon) {
    os << "sly::core::type::Token::Type::kEpsilon";
  } else {
    exit(1);
  }
  return os;
}


void Token::PrintImpl(std::ostream& os) const {
  os << "sly::core::type::Token(\"" << translate_to_raw_form(GetTokName()) << "\",";
  auto type = GetTokenType();
  auto attr= GetAttr();
  if (type == Token::Type::kTerminator) {
    os << "sly::core::type::Token::Type::kTerminator";
  } else if (type == Token::Type::kNonTerminator) {
    os << "sly::core::type::Token::Type::kNonTerminator";
  } else if (type == Token::Type::kEpsilon) {
    os << "sly::core::type::Token::Type::kEpsilon";
  } else {
    exit(1);
  }
  os << "," << GetTid() << ",";
  if (attr == Token::Attr::kLeftAssociative) {
    os << "sly::core::type::Token::Attr::kLeftAssociative";
  } else if (attr == Token::Attr::kRightAssociative) {
    os << "sly::core::type::Token::Attr::kRightAssociative";
  } else if (attr == Token::Attr::kNone) {
    os << "sly::core::type::Token::Attr::kNone";
  } else {
    spdlog::error("{}",(int) attr);
    exit(1);
  }
  os << ")";
}

string Token::ToString() const{
  stringstream ss;
  ss << *this;
  return ss.str();
}

}