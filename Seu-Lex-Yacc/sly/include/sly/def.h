//
// Created by Yang Jerry on 2022/3/30.
//
#include <cstddef>


#ifndef SEULEXYACC_LY_H
#define SEULEXYACC_LY_H

#ifndef EPSILON
#define EPSILON ((char) 0xFF)
#endif

#ifndef DFA_ENTRY_STATE_ID
#define DFA_ENTRY_STATE_ID 0
#endif

#ifndef YYSTATE
#define YYSTATE sly::core::type::AttrDict
#endif
namespace sly{
// TODO: 这个好像根本不需要？
constexpr int INT =  258;
constexpr int FLOAT =  259;
constexpr int NAME =  260;
constexpr int STRUCT =  261;
constexpr int IF =  262;
constexpr int ELSE =  263;
constexpr int RETURN =  264;
constexpr int NUMBER =  265;
constexpr int LPAR =  266;
constexpr int RPAR =  267;
constexpr int LBRACE =  268;
constexpr int RBRACE =  269;
constexpr int LBRACK =  270;
constexpr int RBRACK =  271;
constexpr int ASSIGN =  272;
constexpr int SEMICOLON =  273;
constexpr int COMMA =  274;
constexpr int DOT =  275;
constexpr int PLUS =  276;
constexpr int MINUS =  277;
constexpr int TIMES =  278;
constexpr int DIVIDE =  279;
constexpr int EQUAL =  280;
constexpr int LOW =  281;
constexpr int UMINUS =  282;
}
namespace sly {
namespace core {

namespace type {

using IdType = size_t;
// 替代 Union
class AttrDict;

using TokenAttr = YYSTATE;

class Token;

class Production;

class Action;

class AnnotatedParseTree;

}

namespace lexical {

class NfaModel;

class DfaModel;

class RegEx;
}

namespace grammar {
class ContextFreeGrammar;

class ParsingTable;

class TableGenerateMethod;

class Lr1;

class Lalr;

/**
 * 给定 `ParsingTable` 和 stream<Token> 进行识别
 */
class LrParser;

}
}

namespace utils{}

namespace lex {

class LexParser;



}
namespace yacc {

class YaccParser;


}

namespace runtime {

extern YYSTATE yylval;

class SeuLex;

class SeuYacc;

class Stream2TokenPipe;

}
}

#endif //SEULEXYACC_LY_H
