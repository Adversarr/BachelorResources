//
// Created by Yang Jerry on 2022/3/30.
//

#include "sly/Production.h"
#include "sly/Token.h"
#include "spdlog/fmt/bundled/core.h"
#include "spdlog/spdlog.h"
#include <ostream>
#include <sly/TableGenerateMethod.h>
#include <sly/def.h>
#include <sly/utils.h>
#include <sstream>
#include <string>
#include <unordered_map>
namespace sly::core::grammar {

ParsingTable::ParsingTable(int n_states) {
  for (int i = 0; i < n_states; ++i) {
    action_table_.emplace_back();
    goto_table_.emplace_back();
  }
}

void ParsingTable::SetAllToError(const vector<Token> &token_list) {
  for (auto &action_line : action_table_) {
    for (const auto &token : token_list) {
      if (action_line.find(token) == action_line.end()) {

        action_line.insert(
            {token,
             std::vector<CellTp>{CellTp{
                 .action =
                     sly::core::grammar::ParsingTable::AutomataAction::kError,
                 .id = 0,
                 .cause = {}}}});
      }
    }
  }
}

void ParsingTable::Reset() {
  action_table_.clear();
  goto_table_.clear();
}

bool ParsingTable::PutAction(IdType lhs, const Token &tok,
                             ParsingTable::CellTp action) {
  auto f = action_table_[lhs].find(tok);
  if (f != action_table_[lhs].end()) {
    if (action.action == kAccept)
      f->second = {action};
    else
      f->second.push_back(action);
  }
  action_table_[lhs].insert({tok, {action}});

  string acts;
  if (action.action == AutomataAction::kEmpty)
    acts = "?";
  else if (action.action == AutomataAction::kShiftIn)
    acts = "Sft";
  else if (action.action == AutomataAction::kReduce)
    acts = "Red";
  else if (action.action == AutomataAction::kAccept)
    acts = "Acc";
  else
    acts = "Err";
  spdlog::debug("Putting ACTION: StateID: {} Token: {}\t Action: {} {}", lhs,
                tok.ToString(), acts, action.id);

  return true;
}

void ParsingTable::PutActionForce(IdType lhs, const Token &tok, CellTp action) {
  action_table_[lhs][tok] = {std::move(action)};
}

bool ParsingTable::PutGoto(IdType lhs, const Token &tok, IdType rhs) {
  auto f = goto_table_[lhs].find(tok);
  if (f != goto_table_[lhs].end())
    f->second.push_back(rhs);
  goto_table_[lhs].insert({tok, {rhs}});
  spdlog::debug("Putting  GOTO : From: {} To: {} \t Token{}", lhs, rhs,
                utils::ToString{}(tok));

  return true;
}

void ParsingTable::PutGotoForce(IdType lhs, const Token &tok, IdType rhs) {
  goto_table_[lhs][tok] = {rhs};
}

vector<ParsingTable::CellTp> ParsingTable::GetAction(IdType lhs,
                                                     const Token &tok) const {
  auto f = action_table_[lhs].find(tok);
  if (f != action_table_[lhs].end())
    return f->second;
  else
    return {};
}

vector<IdType> ParsingTable::GetGoto(IdType lhs, const Token &tok) const {
  auto f = goto_table_[lhs].find(tok);
  if (f != goto_table_[lhs].end())
    return f->second;
  else
    return {};
}

void ParsingTable::Print(ostream &os) const {
  os << "sly::core::grammar::ParsingTable(";
  os << std::endl << "  ";
  // print out action table:
  os << "{";
  for (const auto &line : action_table_) {
    os << "{";
    for (auto [token, cell] : line) {
      os << "{";
      // print token:
      // Token(token.GetTokName(), token.GetTokenType(), token.GetTid(),
      // token.GetAttr());
      token.PrintImpl(os);
      // Print comma.
      os << ", {";
      // print cell:
      for (const auto &c : cell) {
        os << c << ",";
      }
      os << "}},";
    }
    os << "}, ";
  }
  os << "}, ";
  os << std::endl << "  ";
  // print out goto
  os << "{";
  for (const auto &line : goto_table_) {
    os << "{";
    for (const auto &[token, go] : line) {
      os << "{";
      token.PrintImpl(os);
      os << ",{";
      for (auto v : go) {
        os << v << ",";
      }
      os << "}},";
    }
    os << "},";
  }
  os << "}, ";
  os << std::endl << "  ";

  os << "productions";
  os << ",";
  os << std::endl << "  ";

  // several tokens
  entry_token_.PrintImpl(os);
  os << ",";
  os << std::endl << "  ";
  augmented_token_.PrintImpl(os);
  os << ",";
  os << std::endl << "  ";
  epsilon_token_.PrintImpl(os);
  os << std::endl << "  ";
  os << ")";
}

void ParsingTable::PrintGeneratorCode(ostream &os) const {
  // table = ...
  // Generate tokens.
  unordered_set<Token, Token::Hash> token_set;
  for (const auto &line : action_table_) {
    for (const auto &[token, cell] : line) {
      token_set.insert(token);
    }
  }
  for (const auto &line : productions_) {
    for (const auto &token : line.GetTokens()) {
      token_set.insert(token);
    }
  }
  vector<Token> tokens{token_set.begin(), token_set.end()};
  stringstream ss;
  ss << "{";
  unordered_map<Token, int, Token::Hash> tok2id;
  for (int i = 0; i < tokens.size(); ++i) {
    tok2id.insert({tokens[i], i});
    tokens[i].PrintImpl(ss);
    if (i != tokens.size())
      ss << ",\n";
  }
  ss << "}";
  os << "{" << endl;
  os << "std::vector<std::unordered_map<sly::core::type::Token, "
        "std::vector<sly::core::grammar::ParsingTable::CellTp>, "
        "sly::core::type::Token::Hash>> action_table_;"
     << std::endl;
  os << "std::vector<std::unordered_map<sly::core::type::Token, "
        "std::vector<IdType>, sly::core::type::Token::Hash>> goto_table_;"
     << std::endl;
  os << "std::vector<sly::core::type::Production> productions_;" << std::endl;
  os << "sly::core::type::Token entry_token_;" << std::endl;
  os << "sly::core::type::Token augmented_token_;" << std::endl;
  os << "sly::core::type::Token epsilon_token_;" << std::endl;
  os << "std::vector<sly::core::type::Token> __tokens_in_use" << ss.str() << ";"
     << std::endl;
  os << std::endl;
  os << "// action_table_" << std::endl;
  os << "{" << std::endl;

  for (const auto &line : action_table_) {
    os << "  action_table_.push_back(std::unordered_map<Token, "
          "std::vector<sly::core::grammar::ParsingTable::CellTp>, Token::Hash>{"
       << std::endl;
    for (const auto &[token, cell] : line) {
      os << "    {";
      // print token:
      // Token(token.GetTokName(), token.GetTokenType(), token.GetTid(),
      // token.GetAttr());
      // token.PrintImpl(os);
      os << "__tokens_in_use[" << tok2id[token] << "]";
      // Print comma.
      os << ", std::vector<sly::core::grammar::ParsingTable::CellTp>{";
      // print cell:
      for (const auto &c : cell) {
        os << c << ",";
      }
      os << "}}," << std::endl;
    }
    os << "  }); " << std::endl;
  }
  os << "}" << std::endl;
  os << std::endl;

  os << "// goto_table_" << std::endl;
  os << "{" << std::endl;
  for (const auto &line : goto_table_) {
    os << "  goto_table_.push_back(std::unordered_map<sly::core::type::Token, "
          "vector<unsigned long>, sly::core::type::Token::Hash>{"
       << std::endl;
    for (const auto &[token, go] : line) {
      os << "    {";
      // token.PrintImpl(os);
      os << "__tokens_in_use[" << tok2id[token] << "]";
      os << ", vector<unsigned long>{";
      for (auto v : go) {
        os << v << ",";
      }
      os << "}}," << std::endl;
    }
    os << "  });" << std::endl;
  }
  os << "}" << std::endl;
  os << std::endl;

  os << "productions_ = productions;" << std::endl;

  os << "entry_token_ = ";
  entry_token_.PrintImpl(os);
  os << ";" << std::endl;

  os << "augmented_token_ = ";
  augmented_token_.PrintImpl(os);
  os << ";" << std::endl;

  os << "epsilon_token_ = ";
  epsilon_token_.PrintImpl(os);
  os << ";" << std::endl;
  os << std::endl;

  os << "table = sly::core::grammar::ParsingTable(" << std::endl;
  os << "  action_table_, goto_table_, productions_, " << std::endl;
  os << "  entry_token_, augmented_token_, epsilon_token_" << std::endl;
  os << ");" << std::endl;
  os << "}" << endl;
}

const vector<unordered_map<Token, vector<ParsingTable::CellTp>, Token::Hash>> &
ParsingTable::GetActionTable() const {
  return action_table_;
}

void ParsingTable::SetActionTable(
    const vector<unordered_map<Token, vector<CellTp>, Token::Hash>>
        &action_table) {
  action_table_ = action_table;
}

const vector<unordered_map<Token, vector<IdType>, Token::Hash>> &
ParsingTable::GetGotoTable() const {
  return goto_table_;
}

void ParsingTable::SetGotoTable(
    const vector<unordered_map<Token, vector<IdType>, Token::Hash>>
        &goto_table) {
  goto_table_ = goto_table;
}

const Token &ParsingTable::GetEntryToken() const { return entry_token_; }

void ParsingTable::SetEntryToken(const Token &entry_token) {
  entry_token_ = entry_token;
}

const Token &ParsingTable::GetAugmentedToken() const {
  return augmented_token_;
}

void ParsingTable::SetAugmentedToken(const Token &augmented_token) {
  augmented_token_ = augmented_token;
}

const Token &ParsingTable::GetEndingToken() const { return ending_token_; }

void ParsingTable::SetEndingToken(const Token &ending_token) {
  ending_token_ = ending_token;
}

const Token &ParsingTable::GetEpsilonToken() const { return epsilon_token_; }

void ParsingTable::SetEpsilonToken(const Token &epsilon_token) {
  epsilon_token_ = epsilon_token;
}

const vector<type::Production> &ParsingTable::GetProductions() const {
  return productions_;
}

void ParsingTable::SetProductions(const vector<type::Production> &productions) {
  productions_ = productions;
}

const ParsingTable &TableGenerateMethod::GetParsingTable() const {
  return lr_table_;
}

ParsingTable ParsingTable::FromRaw(
    std::vector<std::unordered_map<Token, std::vector<CellTp>, Token::Hash>>
        action_table,
    std::vector<std::unordered_map<Token, std::vector<IdType>, Token::Hash>>
        goto_table,
    vector<type::Production> productions, Token entry_token,
    Token augmented_token, Token epsilon_token) {
  ParsingTable pt;
  pt.SetProductions(productions);
  pt.SetActionTable(action_table);
  pt.SetGotoTable(goto_table);
  pt.SetEntryToken(entry_token);
  pt.SetAugmentedToken(augmented_token);
  pt.SetEpsilonToken(epsilon_token);
  return pt;
}

ParsingTable::ParsingTable(
    std::vector<std::unordered_map<Token, std::vector<CellTp>, Token::Hash>>
        action_table,
    std::vector<std::unordered_map<Token, std::vector<IdType>, Token::Hash>>
        goto_table,
    vector<type::Production> productions, Token entry_token,
    Token augmented_token, Token epsilon_token)
    : productions_(productions), action_table_(action_table),
      goto_table_(goto_table), entry_token_(entry_token),
      augmented_token_(augmented_token), epsilon_token_(epsilon_token) {
  productions_.insert(productions_.begin(),
                      type::Production(augmented_token_)(entry_token));
}

ostream &operator<<(ostream &os, const ParsingTable::CellTp &cell) {
  os << "sly::core::grammar::ParsingTable::CellTp{";
  if (cell.action == ParsingTable::kReduce) {
    os << ".action = "
          "sly::core::grammar::ParsingTable::AutomataAction::kReduce,";
  } else if (cell.action == ParsingTable::kAccept) {
    os << ".action = "
          "sly::core::grammar::ParsingTable::AutomataAction::kAccept,";
  } else if (cell.action == ParsingTable::kEmpty) {
    os << ".action = sly::core::grammar::ParsingTable::AutomataAction::kEmpty,";
  } else if (cell.action == ParsingTable::kShiftIn) {
    os << ".action = "
          "sly::core::grammar::ParsingTable::AutomataAction::kShiftIn,";
  } else {
    os << ".action = sly::core::grammar::ParsingTable::AutomataAction::kError,";
  }
  os << ".id=" << cell.id << ", .cause={";
  if (!cell.cause.empty()) {
    for (int i = 0; i < cell.cause.size() - 1; ++i) {
      os << cell.cause[i] << ", ";
    }
    os << cell.cause.back();
  }
  os << "}}";
  return os;
}

bool ParsingTable::CellTp::operator==(const CellTp &rhs) const {
  return this->action == rhs.action && this->id == rhs.id &&
         this->cause == rhs.cause;
}

bool ParsingTable::operator==(const ParsingTable &rhs) const {
  bool flag;
  flag = productions_ == rhs.productions_;
  spdlog::debug("comparing productions={}", flag);
  flag = action_table_ == rhs.action_table_;
  spdlog::debug("comparing action={}", flag);
  flag = goto_table_ == rhs.goto_table_;
  spdlog::debug("comparing goto={}", flag);
  flag = entry_token_ == rhs.entry_token_;
  spdlog::debug("comparing entry={}", flag);
  flag = augmented_token_ == rhs.augmented_token_;
  spdlog::debug("comparing augmented={}", flag);
  flag = epsilon_token_ == rhs.epsilon_token_;
  spdlog::debug("comparing epsilon={}", flag);
  return productions_ == rhs.productions_ &&
         action_table_ == rhs.action_table_ && goto_table_ == rhs.goto_table_ &&
         entry_token_ == rhs.entry_token_ &&
         augmented_token_ == rhs.augmented_token_ &&
         epsilon_token_ == rhs.epsilon_token_;
}
void ParsingTable::PrintGeneratorCodeOpti(ostream &os) const {
  unordered_set<Token, Token::Hash> token_set;
  for (const auto &line : action_table_) {
    for (const auto &[token, cell] : line) {
      token_set.insert(token);
    }
  }
  for (const auto &line : productions_) {
    for (const auto &token : line.GetTokens()) {
      token_set.insert(token);
    }
  }
  vector<Token> tokens{token_set.begin(), token_set.end()};
  stringstream ss;
  ss << "{";
  unordered_map<Token, int, Token::Hash> tok2id;
  for (int i = 0; i < tokens.size(); ++i) {
    tok2id.insert({tokens[i], i});
    tokens[i].PrintImpl(ss);
    if (i != tokens.size())
      ss << ",\n";
  }
  ss << "}";


  string fcall_arguments = R"(const vector<Production> &productions,
                              const sly::core::type::Token &start_syntax_token,
                              const sly::core::type::Token &ending,
                              sly::core::grammar::ParsingTable& table,
                              std::vector<std::unordered_map<sly::core::type::Token, std::vector<sly::core::grammar::ParsingTable::CellTp>, sly::core::type::Token::Hash>>& action_table_,
                              std::vector<std::unordered_map<sly::core::type::Token, std::vector<IdType>, sly::core::type::Token::Hash>>& goto_table_,
                              std::vector<sly::core::type::Token>& __tokens_in_use)";
  string fcall_name = "_apply";
  int count_func = 0;

  auto runtime_fcall = [&]() {
    return fmt::format("{}{}(productions, start_syntax_token, ending, table, "
                       "action_table_, goto_table_, __tokens_in_use);",
                       fcall_name, count_func);
  };
  auto compose = [&](string fbody) {
    return "void " + fcall_name + to_string(count_func) + " (" +
           fcall_arguments + ") {" + "\n" + fbody + "\n}\n";
  };
  string cache = "";
  vector<string> composed_function_impl;
  string defer_table_function_impl = "";
  {
    stringstream os;
    os << R"(void _defer_table(const vector<Production> &productions,
                  const sly::core::type::Token &start_syntax_token,
                  const sly::core::type::Token &ending,
                  sly::core::grammar::ParsingTable& table) {{)"
       << endl;
    os << "std::vector<std::unordered_map<sly::core::type::Token, "
          "std::vector<sly::core::grammar::ParsingTable::CellTp>, "
          "sly::core::type::Token::Hash>> action_table_;"
       << std::endl;
    os << "std::vector<std::unordered_map<sly::core::type::Token, "
          "std::vector<IdType>, sly::core::type::Token::Hash>> goto_table_;"
       << std::endl;
    os << "std::vector<sly::core::type::Production> productions_;" << std::endl;
    os << "sly::core::type::Token entry_token_;" << std::endl;
    os << "sly::core::type::Token augmented_token_;" << std::endl;
    os << "sly::core::type::Token epsilon_token_;" << std::endl;
    os << "std::vector<sly::core::type::Token> __tokens_in_use" << ss.str()
       << ";" << std::endl;
    os << std::endl;
    os << "// action_table_" << std::endl;
    os << "{" << std::endl;
    os << "table=sly::core::grammar::ParsingTable(" << action_table_.size()
       << ");" << endl;

    for (const auto &line : action_table_) {
      // replace os
      {
        stringstream os;
        os << "  action_table_.push_back(std::unordered_map<Token, "
              "std::vector<sly::core::grammar::ParsingTable::CellTp>, "
              "Token::Hash>{"
           << std::endl;
        for (const auto &[token, cell] : line) {
          if (cell.front().action == kError) {
            continue;
          }
          os << "    {";
          // print token:
          // Token(token.GetTokName(), token.GetTokenType(), token.GetTid(),
          // token.GetAttr());
          // token.PrintImpl(os);
          os << "__tokens_in_use[" << tok2id[token] << "]";
          // Print comma.
          os << ", std::vector<sly::core::grammar::ParsingTable::CellTp>{";
          // print cell:
          for (const auto &c : cell) {
            os << c << ",";
          }
          os << "}}," << std::endl;
        }
        os << "  }); " << std::endl;
        cache = cache + "\n\n" + os.str();
      }
      if (cache.length() > 16384) {
        auto fc = runtime_fcall();
        auto fb = compose(cache);
        os << "// call function to modify" << endl;
        os << fc << endl << endl;
        composed_function_impl.push_back(fb);
        count_func += 1;
        cache = "";
      }
    }


    os << "}" << std::endl;
    os << std::endl;

    os << "// goto_table_" << std::endl;
    os << "{" << std::endl;
    for (const auto &line : goto_table_) {
      {
        stringstream os;
      os << "  "
            "goto_table_.push_back(std::unordered_map<sly::core::type::Token, "
            "vector<unsigned long>, sly::core::type::Token::Hash>{"
         << std::endl;
      for (const auto &[token, go] : line) {
        os << "    {";
        // token.PrintImpl(os);
        os << "__tokens_in_use[" << tok2id[token] << "]";
        os << ", vector<unsigned long>{";
        for (auto v : go) {
          os << v << ",";
        }
        os << "}}," << std::endl;
      }
      os << "  });" << std::endl;cache = cache + "\n\n" + os.str();
      }
      if (cache.length() > 16384) {
        auto fc = runtime_fcall();
        auto fb = compose(cache);
        os << "// call function to modify" << endl;
        os << fc << endl << endl;
        composed_function_impl.push_back(fb);
        count_func += 1;
        cache = "";
      }
    }
    auto fc = runtime_fcall();
    auto fb = compose(cache);
    composed_function_impl.push_back(fb);
    os << "// call function to modify" << endl;
    os << fc << endl << endl;
    count_func += 1;
    cache = "";
    os << "}" << std::endl;
    os << std::endl;

    os << "productions_ = productions;" << std::endl;

    os << "entry_token_ = ";
    entry_token_.PrintImpl(os);
    os << ";" << std::endl;

    os << "augmented_token_ = ";
    augmented_token_.PrintImpl(os);
    os << ";" << std::endl;

    os << "epsilon_token_ = ";
    epsilon_token_.PrintImpl(os);
    os << ";" << std::endl;
    os << std::endl;

    os << "table = sly::core::grammar::ParsingTable(" << std::endl;
    os << "  action_table_, goto_table_, productions_, " << std::endl;
    os << "  entry_token_, augmented_token_, epsilon_token_" << std::endl;
    os << ");" << std::endl;
    os << "table.SetAllToError(__tokens_in_use);";
    os << "}}" << endl;
    defer_table_function_impl = os.str();
  }

  for (const auto& impl: composed_function_impl) {
    os << impl << endl;
  }
  os << defer_table_function_impl << endl;
}

} // namespace sly::core::grammar