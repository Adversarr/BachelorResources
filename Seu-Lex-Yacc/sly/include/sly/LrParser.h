#ifndef LRPARSER_H
#define LRPARSER_H

#include "def.h"
#include "ContextFreeGrammar.h"
#include "AnnotatedParseTree.h"

#include <optional>
#include <stack>

using namespace std;


namespace sly::core::grammar {

class LrParser {
 public:
  explicit LrParser(ParsingTable& parsing_table);
  
  void Parse(vector<Token> token_stream, vector<YYSTATE> yylval_stream);

  void ParseStep(const vector<Token>& token_stream, const vector<YYSTATE>& yylval_stream);
  
  const ParsingTable &GetPt() const;
  
  void SetPt(const ParsingTable &pt);
  
  AnnotatedParseTree GetTree() const;
 
 private:
  vector<Token> stream;
  
  void ParseOnce(const vector<Token>& token_stream, const vector<YYSTATE>& yylval_stream);
  
  ParsingTable pt_;
  
  std::deque<AnnotatedParseTree> apt_stack_;
  
  std::deque<IdType > state_stack_;
  
  IdType current_state_id_;
  
  IdType current_offset_;
  
  unordered_map<Token, type::Action, Token::Hash> token_actions_;

  bool accepted_;
};
}


#endif // LRPARSER_H
