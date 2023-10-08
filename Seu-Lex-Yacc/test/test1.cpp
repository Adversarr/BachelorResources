//
// Created by Yang Jerry on 2022/3/30.
//

#include "sly/AttrDict.h"
#include "sly/FaModel.h"
#include "sly/LrParser.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <sly/sly.h>

#include <iostream>
#include <sstream>
#include <vector>

using sly::core::type::AttrDict;
using sly::core::type::Production;
using sly::core::type::Token;

using namespace std;

int main() {
  spdlog::set_level(spdlog::level::warn);

  // 定义文法
  // 1. 定义tokens
  auto add = Token::Terminator("+", Token::Attr::kLeftAssociative);
  auto sub = Token::Terminator("-", Token::Attr::kLeftAssociative);
  auto multi = Token::Terminator("*", Token::Attr::kLeftAssociative);
  auto div = Token::Terminator("/", Token::Attr::kLeftAssociative);
  auto alpha = Token::Terminator("a");
  auto lb = Token::Terminator("(");
  auto rb = Token::Terminator(")");
  auto blank = Token::Terminator("blank");
  auto ending = Token::Terminator("EOF_FLAG");
  auto expr = Token::NonTerminator("Expr");
  auto fact = Token::NonTerminator("Fact");
  sly::core::lexical::RegEx re_add("\\+");
  sly::core::lexical::RegEx re_blank("( |\n|\t)");
  sly::core::lexical::RegEx re_sub("\\-");
  sly::core::lexical::RegEx re_multi("\\*");
  sly::core::lexical::RegEx re_div("/");
  sly::core::lexical::RegEx re_alpha("[0-9]+");
  sly::core::lexical::RegEx re_lb("\\(");
  sly::core::lexical::RegEx re_rb("\\)");
  vector<Production> productions = {
      // expr -> expr + expr
      Production(expr, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value", v[1].Get<int>("value") +
                                              v[3].Get<int>("value"));
                 }})(expr)(add)(expr),
      // expr -> expr - expr
      Production(expr, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value", v[1].Get<int>("value") -
                                              v[3].Get<int>("value"));
                 }})(expr)(sub)(expr),
      // expr -> fact
      Production(expr, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value", v[1].Get<int>("value"));
                 }})(fact),
      // fact -> fact * fact
      Production(fact, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value", v[1].Get<int>("value") *
                                              v[3].Get<int>("value"));
                 }})(fact)(multi)(fact),
      // fact -> fact / fact
      Production(fact, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value", v[1].Get<int>("value") /
                                              v[3].Get<int>("value"));
                 }})(fact)(div)(fact),
      // fact -> ( expr )
      Production(fact, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value", v[2].Get<int>("value"));
                 }})(lb)(expr)(rb),
      // fact -> alpha
      Production(fact, {[](vector<YYSTATE> &v) {
                   v[0].Set<int>("value",
                                 atoi(v[1].Get<string>("lval").c_str()));
                 }})(alpha),
  };
  sly::core::grammar::ContextFreeGrammar cfg(productions, expr, ending);
  sly::core::grammar::Lr1 lr1;
  cfg.Compile(lr1);
  auto table = cfg.GetLrTable();
  sly::core::grammar::LrParser parser(table);

  // 定义词法 transition 和 state
  auto [transition, state] = sly::core::lexical::DfaModel::Merge(
      {re_add.GetDfaModel(), re_alpha.GetDfaModel(), re_div.GetDfaModel(),
       re_lb.GetDfaModel(), re_multi.GetDfaModel(), re_rb.GetDfaModel(),
       re_sub.GetDfaModel(), re_blank.GetDfaModel()});
  auto s2ppl = sly::runtime::Stream2TokenPipe(
      transition, state, {add, alpha, div, lb, multi, rb, sub, blank}, ending);

  string input_string /* = "(1+2)*3"*/;
  cout << "Input Expr: ";
  cin >> input_string;
  cout << "The Expr: " << input_string << endl;
  stringstream input_stream(input_string);
  vector<AttrDict> attributes;
  vector<Token> tokens;
  while (true) {
    auto token = s2ppl.Defer(input_stream);
    if (token == blank)
      continue;
    AttrDict ad;
    ad.Set("lval", s2ppl.buffer_);
    ad.Set("row", s2ppl.row_);
    ad.Set("col", s2ppl.col_);
    tokens.emplace_back(token);
    attributes.emplace_back(ad);
    if (token == ending)
      break;
  }
  parser.Parse(tokens, attributes);

  auto tree = parser.GetTree();
  cout << "\n\nBefore Annotate.: " << endl;
  tree.Print(std::cout);
  tree.Annotate();
  cout << "\n\nAfter Annotate:" << endl;
  tree.Print(std::cout);
  cout << "\n\nThe Expr: " << input_string << endl;
  cout << "Evaluated : " << tree.GetRootAttributes()[0].Get<int>("value")
       << endl;
  return 0;
}
