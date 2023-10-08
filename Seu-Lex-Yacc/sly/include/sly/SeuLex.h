//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_SEULEX_H
#define SEULEXYACC_SEULEX_H
#include "def.h"
#include <array>
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include "AttrDict.h"
#include "Token.h"


namespace sly::runtime {

constexpr size_t LEX_BUFFER_SIZE = 4096;

// Run and return id.
class SeuLex {
 public:
  using Token = core::type::Token;

  void Process();

 private:
  std::vector<std::array<int, 128>> table_;
  
  std::vector<Token> tokens_;
  
  YYSTATE yylval;

  std::istream* yyin;

  std::ostream* yyout;

};

// yyin 和yyout ：这是Lex中本身已定义的输入和输出文件指针。这两个变量指明了lex生成的词法分析器从哪里获得输入和输出到哪里。默认：键盘输入，屏幕输出。
// yytext 和yyleng ：这也是lex中已定义的变量，直接用就可以了。
// yytext ：指向当前识别的词法单元（词文）的指针
// yyleng ：当前词法单元的长度。
// ECHO ：Lex中预定义的宏，可以出现在动作中，相当于fprintf(yyout, “%s”,yytext)，即输出当前匹配的词法单元。
// yylex() ：词法分析器驱动程序，用Lex翻译器生成的lex.yy.c 内必然含有这个函数。
// yywrap() ：词法分析器遇到文件结尾时会调用yywrap() 来决定下一步怎么做；若yywrap() 返回0 ，则继续扫描；若返回1 ，则返回报告文件结尾的0标记。


}

#endif //SEULEXYACC_SEULEX_H
