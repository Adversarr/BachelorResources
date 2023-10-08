
  void _defer_table(const vector<Production> &productions,
                    const sly::core::type::Token &start_syntax_token,
                    const sly::core::type::Token &ending,
                    sly::core::grammar::ParsingTable& table) {
    // syntax
    sly::core::grammar::ContextFreeGrammar cfg(productions, start_syntax_token, ending);
    sly::core::grammar::Lr1 lr1;
    cfg.Compile(lr1);
    table = cfg.GetLrTable();
    // rewrite
    ofstream outputFile("../test/out_precompile.cpp");
    table.PrintGeneratorCodeOpti(outputFile);
    outputFile.close();
    // return 0;
  }
  