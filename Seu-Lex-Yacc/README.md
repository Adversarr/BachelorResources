# Seu - Lex - Yacc (libsly)

## 如何运行？很简单的啦！

```bash
# Configure CMake build
cmake -S . -B build -G Ninja
# build SeuLexYacc
cmake --build build --target SeuLexYacc --config Release --
# Run SeuLexYacc
./build/standalone/SeuLexYacc
# Build output 
cmake --build build --target output --config Release --
# backup original version
cp ./build/standalone/output ./build/standalone/output_no_precompile_backup
./build/standalone/output
# build precompiled version
cmake --build build --target output --config Release -- ./build/standalone/output
```

## 简介

几个模块：

1. core
   1. type
      1. Token -- 作为 LR 的识别符号和 Lex 产生的符号
      2. Production
      3. Action
      4. ContextFreeGrammar
      5. AttrDict 作为 Union 的替代品
   2. lexical
      1. NfaModel -- NFA 的 Model
      2. DfaModel
      3. RegEx -- 正则
   3. grammar
      1. TableGenerateMethod -- virtual base class
      2. Lr1
      3. Lalr
      4. ParsingTable
      5. LrParser
2. lex
   1. LexParser -- 处理 `.l` 文件
3. yacc
   1. YaccParser -- 处理 `.y` 文件
4. runtime
   1. yylval
   2. SeuLex
   3. SeuYacc

# TODO

还差 Lex 和 Yacc 的实现

参考：`test1.cpp` 的[实现](test/test1.cpp)。

主要更新位于`test4.cpp`，该文件会读入`../demo/1.l`和`../demo/1.y`，然后将生成的代码写入`../test/out.cpp`。
代码生成的规范可以参考`test5.cpp`。

```bash
$ cd build
$ make test4
$ ./test/test4
$ make out
$ gdb ./test/out
```

目前生成的`out.cpp`还未完成全部排障。
