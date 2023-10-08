
table = sly::core::grammar::ParsingTable(
  // action_table
  {
    {
      {sly::core::type::Token(R"(STRING_LITERAL)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
      {sly::core::type::Token(R"(CONSTANT)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
    }, {
      {sly::core::type::Token(R"(STRING_LITERAL)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
      {sly::core::type::Token(R"(CONSTANT)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
      {sly::core::type::Token(R"(,)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
      {sly::core::type::Token(R"(INT)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kShiftIn,.id=6},}},
    }, {
      {sly::core::type::Token(R"(STRING_LITERAL)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
      {sly::core::type::Token(R"(CONSTANT)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
    }
  }, 

  // goto_table
  {
    {
      {sly::core::type::Token(R"(declaration_specifiers)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{5,}},
      {sly::core::type::Token(R"(declaration)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{4,}},
      {sly::core::type::Token(R"(function_definition)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{3,}},
    },{
    },{
      {sly::core::type::Token(R"(init_declarator)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{9,}},
      {sly::core::type::Token(R"(init_declarator_list)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{8,}},
    },{
    }
  }, 

  // productions
  productions,

  // entry_token
  sly::core::type::Token(R"(translation_unit)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),

  // augmented_token
  sly::core::type::Token(R"(#LR augmented#)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),

  // epsilon_token
  sly::core::type::Token(R"()",sly::core::type::Token::Type::kEpsilon,0,sly::core::type::Token::Attr::kNone)
  );
LrParser parser(table);

// procedure-pattern: 

std::vector<std::unordered_map<Token, std::vector<CellTp>, Token::Hash>> action_table;
std::vector<std::unordered_map<Token, std::vector<IdType>, Token::Hash>> goto_table;
vector<type::Production> productions;
Token entry_token;
Token augmented_token;
Token epsilon_token;

// action table
{
  action_table.push_back({
    {sly::core::type::Token(R"(STRING_LITERAL)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
    {sly::core::type::Token(R"(CONSTANT)",sly::core::type::Token::Type::kTerminator,0,sly::core::type::Token::Attr::kNone), {sly::core::grammar::ParsingTable::CellTp{.action = sly::core::grammar::ParsingTable::AutomataAction::kError,.id=0},}},
  });
}

// goto_table
{
  goto_table.push_back({
    {sly::core::type::Token(R"(declaration_specifiers)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{5,}},
    {sly::core::type::Token(R"(declaration)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{4,}},
    {sly::core::type::Token(R"(function_definition)",sly::core::type::Token::Type::kNonTerminator,0,sly::core::type::Token::Attr::kNone),{3,}},
  });
  goto_table.push_back({
  });
}