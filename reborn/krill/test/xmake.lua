target('test_automata')
  add_files('test_automata.cpp')
  add_deps('krill')
target('test_grammar')
  add_files('test_grammar.cpp')
  add_deps('krill')
target('test_lexical')
  add_files('test_lexical.cpp')
  add_deps('krill')
target('test_regex')
  add_files('test_regex.cpp')
  add_deps('krill')
target('test_syntax')
  add_files('test_syntax.cpp')
  add_deps('krill')

