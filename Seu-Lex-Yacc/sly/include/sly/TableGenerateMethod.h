//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_TABLEGENERATEMETHOD_H
#define SEULEXYACC_TABLEGENERATEMETHOD_H
#include "def.h"
#include "Token.h"
#include "Production.h"
#include <vector>
#include <unordered_map>

using sly::core::type::IdType;

using sly::core::type::Token;


namespace sly::core::grammar {
class ParsingTable
{
 public:

  enum AutomataAction{
    kAccept, kReduce, kShiftIn, kError, kEmpty
  };
  
  struct CellTp {
    AutomataAction action = kError;
    IdType id = 0;
    vector<IdType> cause;
    bool operator ==(const CellTp& rhs) const;
  };
  
  explicit ParsingTable(int n_states=0);
  
  void SetAllToError(const vector<Token>& token_list);

  bool PutAction(IdType lhs, const Token& tok, CellTp action);
  
  void PutActionForce(IdType lhs, const Token& tok, CellTp action);
  
  bool PutGoto(IdType lhs, const Token& tok, IdType rhs);
  
  void PutGotoForce(IdType lhs, const Token& tok, IdType rhs);
  
  vector<CellTp> GetAction(IdType lhs, const Token& tok) const;
  
  vector<IdType> GetGoto(IdType lhs, const Token& tok) const;
  
  void Reset();
  
  void Print(ostream& os) const;

  void PrintGeneratorCode(ostream &os) const;

  void PrintGeneratorCodeOpti(ostream &os) const;

  
  const vector<unordered_map<Token, vector<CellTp>, Token::Hash>> &GetActionTable() const;
  
  void SetActionTable(const vector<unordered_map<Token, vector<CellTp>, Token::Hash>> &action_table);
  
  const vector<unordered_map<Token, vector<IdType>, Token::Hash>> &GetGotoTable() const;
  
  void SetGotoTable(const vector<unordered_map<Token, vector<IdType>, Token::Hash>> &goto_table);
  
  const Token &GetEntryToken() const;
  
  void SetEntryToken(const Token &entry_token);
  
  const Token &GetAugmentedToken() const;
  
  void SetAugmentedToken(const Token &augmented_token);
  
  const Token &GetEndingToken() const;
  
  void SetEndingToken(const Token &ending_token);
  
  const Token &GetEpsilonToken() const;
  
  void SetEpsilonToken(const Token &epsilon_token);
 
  const vector<type::Production> &GetProductions() const;
  
  void SetProductions(const vector<type::Production> &productions);
  explicit ParsingTable (
    std::vector<std::unordered_map<Token, std::vector<CellTp>, Token::Hash>> action_table,
    std::vector<std::unordered_map<Token, std::vector<IdType>, Token::Hash>> goto_table,
    vector<type::Production> productions,
    Token entry_token,
    Token augmented_token,
    Token epsilon_token
  );

  static ParsingTable FromRaw(
    std::vector<std::unordered_map<Token, std::vector<CellTp>, Token::Hash>> action_table,
    std::vector<std::unordered_map<Token, std::vector<IdType>, Token::Hash>> goto_table,
    vector<type::Production> productions,
    Token entry_token,
    Token augmented_token,
    Token epsilon_token
  );

  bool operator==(const ParsingTable& rhs) const;
 
 private:
  vector<type::Production> productions_;

  vector<type::Token> tokens_;
  
  std::vector<std::unordered_map<Token, std::vector<CellTp>, Token::Hash>> action_table_;
  
  std::vector<std::unordered_map<Token, std::vector<IdType>, Token::Hash>> goto_table_;
  
  Token entry_token_;
  
  Token augmented_token_;
  
  Token ending_token_;
  
  Token epsilon_token_;
};



class TableGenerateMethod {
 public:
  virtual void Defer(const ContextFreeGrammar& cfg) = 0;
  
  const ParsingTable &GetParsingTable() const;
 
 protected:
  
  const ContextFreeGrammar* p_grammar = nullptr;
  
  ParsingTable lr_table_;
};

ostream& operator<<(ostream& os, const ParsingTable::CellTp& cell);
}

#endif //SEULEXYACC_TABLEGENERATEMETHOD_H
