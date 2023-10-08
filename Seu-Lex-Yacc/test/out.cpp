/* section 1 */
#include "sly/AttrDict.h"
#include "sly/FaModel.h"
#include "sly/LrParser.h"
#include "sly/RegEx.h"
#include "sly/Stream2TokenPipe.h"
#include <sly/sly.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using sly::core::type::AttrDict;
using sly::core::type::Production;
using sly::core::type::Token;
using sly::core::lexical::RegEx;
using sly::core::lexical::DfaModel;
using sly::runtime::Stream2TokenPipe;
using sly::core::grammar::LrParser;
using namespace std;

#define ECHO (cerr << yytext)
#define error(...) {\
  fprintf(stderr, "%s:line %d: ", __FILE__, __LINE__);  \
  fprintf(stderr, __VA_ARGS__);                         \
  fprintf(stderr, "\n");                                \
  exit(1);                                              \
}

/* user code from yacc file start */
#include <stdio.h>

extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


/* user code from yacc file end */

/* user code from lex file start */
#include <stdio.h>

void count(void);

/* user code from lex file end */

/* section 2 */
//@variable
const int num_lexical_tokens = 99;
const int num_syntax_tokens = 131;

auto ending = Token::Terminator("EOF_FLAG");

//@variable
#define ADD_ASSIGN 256
#define AND_ASSIGN 257
#define AND_OP 258
#define AUTO 259
#define BOOL 260
#define BREAK 261
#define CASE 262
#define CHAR 263
#define COMPLEX 264
#define CONST 265
#define CONSTANT 266
#define CONTINUE 267
#define DEC_OP 268
#define DEFAULT 269
#define DIV_ASSIGN 270
#define DO 271
#define DOUBLE 272
#define ELLIPSIS 273
#define ELSE 274
#define ENUM 275
#define EQ_OP 276
#define EXTERN 277
#define FLOAT 278
#define FOR 279
#define GE_OP 280
#define GOTO 281
#define IDENTIFIER 282
#define IF 283
#define IMAGINARY 284
#define INC_OP 285
#define INLINE 286
#define INT 287
#define LEFT_ASSIGN 288
#define LEFT_OP 289
#define LE_OP 290
#define LONG 291
#define MOD_ASSIGN 292
#define MUL_ASSIGN 293
#define NE_OP 294
#define OR_ASSIGN 295
#define OR_OP 296
#define PTR_OP 297
#define REGISTER 298
#define RESTRICT 299
#define RETURN 300
#define RIGHT_ASSIGN 301
#define RIGHT_OP 302
#define SHORT 303
#define SIGNED 304
#define SIZEOF 305
#define STATIC 306
#define STRING_LITERAL 307
#define STRUCT 308
#define SUB_ASSIGN 309
#define SWITCH 310
#define TYPEDEF 311
#define TYPE_NAME 312
#define UNION 313
#define UNSIGNED 314
#define VOID 315
#define VOLATILE 316
#define WHILE 317
#define XOR_ASSIGN 318
#define abstract_declarator 319
#define additive_expression 320
#define and_expression 321
#define argument_expression_list 322
#define assignment_expression 323
#define assignment_operator 324
#define block_item 325
#define block_item_list 326
#define cast_expression 327
#define compound_statement 328
#define conditional_expression 329
#define constant_expression 330
#define declaration 331
#define declaration_list 332
#define declaration_specifiers 333
#define declarator 334
#define designation 335
#define designator 336
#define designator_list 337
#define direct_abstract_declarator 338
#define direct_declarator 339
#define enum_specifier 340
#define enumerator 341
#define enumerator_list 342
#define equality_expression 343
#define exclusive_or_expression 344
#define expression 345
#define expression_statement 346
#define external_declaration 347
#define function_definition 348
#define function_specifier 349
#define identifier_list 350
#define inclusive_or_expression 351
#define init_declarator 352
#define init_declarator_list 353
#define initializer 354
#define initializer_list 355
#define iteration_statement 356
#define jump_statement 357
#define labeled_statement 358
#define logical_and_expression 359
#define logical_or_expression 360
#define multiplicative_expression 361
#define parameter_declaration 362
#define parameter_list 363
#define parameter_type_list 364
#define pointer 365
#define postfix_expression 366
#define primary_expression 367
#define relational_expression 368
#define selection_statement 369
#define shift_expression 370
#define specifier_qualifier_list 371
#define statement 372
#define storage_class_specifier 373
#define struct_declaration 374
#define struct_declaration_list 375
#define struct_declarator 376
#define struct_declarator_list 377
#define struct_or_union 378
#define struct_or_union_specifier 379
#define translation_unit 380
#define type_name 381
#define type_qualifier 382
#define type_qualifier_list 383
#define type_specifier 384
#define unary_expression 385
#define unary_operator 386

/* section 3 */
// syntax tokens 
Token syntax_tokens[256 + num_syntax_tokens] = {
  Token::Terminator(string(1, static_cast<char>(0))), 
  Token::Terminator(string(1, static_cast<char>(1))), 
  Token::Terminator(string(1, static_cast<char>(2))), 
  Token::Terminator(string(1, static_cast<char>(3))), 
  Token::Terminator(string(1, static_cast<char>(4))), 
  Token::Terminator(string(1, static_cast<char>(5))), 
  Token::Terminator(string(1, static_cast<char>(6))), 
  Token::Terminator(string(1, static_cast<char>(7))), 
  Token::Terminator(string(1, static_cast<char>(8))), 
  Token::Terminator(string(1, static_cast<char>(9))), 
  Token::Terminator(string(1, static_cast<char>(10))), 
  Token::Terminator(string(1, static_cast<char>(11))), 
  Token::Terminator(string(1, static_cast<char>(12))), 
  Token::Terminator(string(1, static_cast<char>(13))), 
  Token::Terminator(string(1, static_cast<char>(14))), 
  Token::Terminator(string(1, static_cast<char>(15))), 
  Token::Terminator(string(1, static_cast<char>(16))), 
  Token::Terminator(string(1, static_cast<char>(17))), 
  Token::Terminator(string(1, static_cast<char>(18))), 
  Token::Terminator(string(1, static_cast<char>(19))), 
  Token::Terminator(string(1, static_cast<char>(20))), 
  Token::Terminator(string(1, static_cast<char>(21))), 
  Token::Terminator(string(1, static_cast<char>(22))), 
  Token::Terminator(string(1, static_cast<char>(23))), 
  Token::Terminator(string(1, static_cast<char>(24))), 
  Token::Terminator(string(1, static_cast<char>(25))), 
  Token::Terminator(string(1, static_cast<char>(26))), 
  Token::Terminator(string(1, static_cast<char>(27))), 
  Token::Terminator(string(1, static_cast<char>(28))), 
  Token::Terminator(string(1, static_cast<char>(29))), 
  Token::Terminator(string(1, static_cast<char>(30))), 
  Token::Terminator(string(1, static_cast<char>(31))), 
  Token::Terminator(string(1, static_cast<char>(32))), 
  Token::Terminator(string(1, static_cast<char>(33))), 
  Token::Terminator(string(1, static_cast<char>(34))), 
  Token::Terminator(string(1, static_cast<char>(35))), 
  Token::Terminator(string(1, static_cast<char>(36))), 
  Token::Terminator(string(1, static_cast<char>(37))), 
  Token::Terminator(string(1, static_cast<char>(38))), 
  Token::Terminator(string(1, static_cast<char>(39))), 
  Token::Terminator(string(1, static_cast<char>(40))), 
  Token::Terminator(string(1, static_cast<char>(41))), 
  Token::Terminator(string(1, static_cast<char>(42))), 
  Token::Terminator(string(1, static_cast<char>(43))), 
  Token::Terminator(string(1, static_cast<char>(44))), 
  Token::Terminator(string(1, static_cast<char>(45))), 
  Token::Terminator(string(1, static_cast<char>(46))), 
  Token::Terminator(string(1, static_cast<char>(47))), 
  Token::Terminator(string(1, static_cast<char>(48))), 
  Token::Terminator(string(1, static_cast<char>(49))), 
  Token::Terminator(string(1, static_cast<char>(50))), 
  Token::Terminator(string(1, static_cast<char>(51))), 
  Token::Terminator(string(1, static_cast<char>(52))), 
  Token::Terminator(string(1, static_cast<char>(53))), 
  Token::Terminator(string(1, static_cast<char>(54))), 
  Token::Terminator(string(1, static_cast<char>(55))), 
  Token::Terminator(string(1, static_cast<char>(56))), 
  Token::Terminator(string(1, static_cast<char>(57))), 
  Token::Terminator(string(1, static_cast<char>(58))), 
  Token::Terminator(string(1, static_cast<char>(59))), 
  Token::Terminator(string(1, static_cast<char>(60))), 
  Token::Terminator(string(1, static_cast<char>(61))), 
  Token::Terminator(string(1, static_cast<char>(62))), 
  Token::Terminator(string(1, static_cast<char>(63))), 
  Token::Terminator(string(1, static_cast<char>(64))), 
  Token::Terminator(string(1, static_cast<char>(65))), 
  Token::Terminator(string(1, static_cast<char>(66))), 
  Token::Terminator(string(1, static_cast<char>(67))), 
  Token::Terminator(string(1, static_cast<char>(68))), 
  Token::Terminator(string(1, static_cast<char>(69))), 
  Token::Terminator(string(1, static_cast<char>(70))), 
  Token::Terminator(string(1, static_cast<char>(71))), 
  Token::Terminator(string(1, static_cast<char>(72))), 
  Token::Terminator(string(1, static_cast<char>(73))), 
  Token::Terminator(string(1, static_cast<char>(74))), 
  Token::Terminator(string(1, static_cast<char>(75))), 
  Token::Terminator(string(1, static_cast<char>(76))), 
  Token::Terminator(string(1, static_cast<char>(77))), 
  Token::Terminator(string(1, static_cast<char>(78))), 
  Token::Terminator(string(1, static_cast<char>(79))), 
  Token::Terminator(string(1, static_cast<char>(80))), 
  Token::Terminator(string(1, static_cast<char>(81))), 
  Token::Terminator(string(1, static_cast<char>(82))), 
  Token::Terminator(string(1, static_cast<char>(83))), 
  Token::Terminator(string(1, static_cast<char>(84))), 
  Token::Terminator(string(1, static_cast<char>(85))), 
  Token::Terminator(string(1, static_cast<char>(86))), 
  Token::Terminator(string(1, static_cast<char>(87))), 
  Token::Terminator(string(1, static_cast<char>(88))), 
  Token::Terminator(string(1, static_cast<char>(89))), 
  Token::Terminator(string(1, static_cast<char>(90))), 
  Token::Terminator(string(1, static_cast<char>(91))), 
  Token::Terminator(string(1, static_cast<char>(92))), 
  Token::Terminator(string(1, static_cast<char>(93))), 
  Token::Terminator(string(1, static_cast<char>(94))), 
  Token::Terminator(string(1, static_cast<char>(95))), 
  Token::Terminator(string(1, static_cast<char>(96))), 
  Token::Terminator(string(1, static_cast<char>(97))), 
  Token::Terminator(string(1, static_cast<char>(98))), 
  Token::Terminator(string(1, static_cast<char>(99))), 
  Token::Terminator(string(1, static_cast<char>(100))), 
  Token::Terminator(string(1, static_cast<char>(101))), 
  Token::Terminator(string(1, static_cast<char>(102))), 
  Token::Terminator(string(1, static_cast<char>(103))), 
  Token::Terminator(string(1, static_cast<char>(104))), 
  Token::Terminator(string(1, static_cast<char>(105))), 
  Token::Terminator(string(1, static_cast<char>(106))), 
  Token::Terminator(string(1, static_cast<char>(107))), 
  Token::Terminator(string(1, static_cast<char>(108))), 
  Token::Terminator(string(1, static_cast<char>(109))), 
  Token::Terminator(string(1, static_cast<char>(110))), 
  Token::Terminator(string(1, static_cast<char>(111))), 
  Token::Terminator(string(1, static_cast<char>(112))), 
  Token::Terminator(string(1, static_cast<char>(113))), 
  Token::Terminator(string(1, static_cast<char>(114))), 
  Token::Terminator(string(1, static_cast<char>(115))), 
  Token::Terminator(string(1, static_cast<char>(116))), 
  Token::Terminator(string(1, static_cast<char>(117))), 
  Token::Terminator(string(1, static_cast<char>(118))), 
  Token::Terminator(string(1, static_cast<char>(119))), 
  Token::Terminator(string(1, static_cast<char>(120))), 
  Token::Terminator(string(1, static_cast<char>(121))), 
  Token::Terminator(string(1, static_cast<char>(122))), 
  Token::Terminator(string(1, static_cast<char>(123))), 
  Token::Terminator(string(1, static_cast<char>(124))), 
  Token::Terminator(string(1, static_cast<char>(125))), 
  Token::Terminator(string(1, static_cast<char>(126))), 
  Token::Terminator(string(1, static_cast<char>(127))), 
  Token::Terminator(string(1, static_cast<char>(128))), 
  Token::Terminator(string(1, static_cast<char>(129))), 
  Token::Terminator(string(1, static_cast<char>(130))), 
  Token::Terminator(string(1, static_cast<char>(131))), 
  Token::Terminator(string(1, static_cast<char>(132))), 
  Token::Terminator(string(1, static_cast<char>(133))), 
  Token::Terminator(string(1, static_cast<char>(134))), 
  Token::Terminator(string(1, static_cast<char>(135))), 
  Token::Terminator(string(1, static_cast<char>(136))), 
  Token::Terminator(string(1, static_cast<char>(137))), 
  Token::Terminator(string(1, static_cast<char>(138))), 
  Token::Terminator(string(1, static_cast<char>(139))), 
  Token::Terminator(string(1, static_cast<char>(140))), 
  Token::Terminator(string(1, static_cast<char>(141))), 
  Token::Terminator(string(1, static_cast<char>(142))), 
  Token::Terminator(string(1, static_cast<char>(143))), 
  Token::Terminator(string(1, static_cast<char>(144))), 
  Token::Terminator(string(1, static_cast<char>(145))), 
  Token::Terminator(string(1, static_cast<char>(146))), 
  Token::Terminator(string(1, static_cast<char>(147))), 
  Token::Terminator(string(1, static_cast<char>(148))), 
  Token::Terminator(string(1, static_cast<char>(149))), 
  Token::Terminator(string(1, static_cast<char>(150))), 
  Token::Terminator(string(1, static_cast<char>(151))), 
  Token::Terminator(string(1, static_cast<char>(152))), 
  Token::Terminator(string(1, static_cast<char>(153))), 
  Token::Terminator(string(1, static_cast<char>(154))), 
  Token::Terminator(string(1, static_cast<char>(155))), 
  Token::Terminator(string(1, static_cast<char>(156))), 
  Token::Terminator(string(1, static_cast<char>(157))), 
  Token::Terminator(string(1, static_cast<char>(158))), 
  Token::Terminator(string(1, static_cast<char>(159))), 
  Token::Terminator(string(1, static_cast<char>(160))), 
  Token::Terminator(string(1, static_cast<char>(161))), 
  Token::Terminator(string(1, static_cast<char>(162))), 
  Token::Terminator(string(1, static_cast<char>(163))), 
  Token::Terminator(string(1, static_cast<char>(164))), 
  Token::Terminator(string(1, static_cast<char>(165))), 
  Token::Terminator(string(1, static_cast<char>(166))), 
  Token::Terminator(string(1, static_cast<char>(167))), 
  Token::Terminator(string(1, static_cast<char>(168))), 
  Token::Terminator(string(1, static_cast<char>(169))), 
  Token::Terminator(string(1, static_cast<char>(170))), 
  Token::Terminator(string(1, static_cast<char>(171))), 
  Token::Terminator(string(1, static_cast<char>(172))), 
  Token::Terminator(string(1, static_cast<char>(173))), 
  Token::Terminator(string(1, static_cast<char>(174))), 
  Token::Terminator(string(1, static_cast<char>(175))), 
  Token::Terminator(string(1, static_cast<char>(176))), 
  Token::Terminator(string(1, static_cast<char>(177))), 
  Token::Terminator(string(1, static_cast<char>(178))), 
  Token::Terminator(string(1, static_cast<char>(179))), 
  Token::Terminator(string(1, static_cast<char>(180))), 
  Token::Terminator(string(1, static_cast<char>(181))), 
  Token::Terminator(string(1, static_cast<char>(182))), 
  Token::Terminator(string(1, static_cast<char>(183))), 
  Token::Terminator(string(1, static_cast<char>(184))), 
  Token::Terminator(string(1, static_cast<char>(185))), 
  Token::Terminator(string(1, static_cast<char>(186))), 
  Token::Terminator(string(1, static_cast<char>(187))), 
  Token::Terminator(string(1, static_cast<char>(188))), 
  Token::Terminator(string(1, static_cast<char>(189))), 
  Token::Terminator(string(1, static_cast<char>(190))), 
  Token::Terminator(string(1, static_cast<char>(191))), 
  Token::Terminator(string(1, static_cast<char>(192))), 
  Token::Terminator(string(1, static_cast<char>(193))), 
  Token::Terminator(string(1, static_cast<char>(194))), 
  Token::Terminator(string(1, static_cast<char>(195))), 
  Token::Terminator(string(1, static_cast<char>(196))), 
  Token::Terminator(string(1, static_cast<char>(197))), 
  Token::Terminator(string(1, static_cast<char>(198))), 
  Token::Terminator(string(1, static_cast<char>(199))), 
  Token::Terminator(string(1, static_cast<char>(200))), 
  Token::Terminator(string(1, static_cast<char>(201))), 
  Token::Terminator(string(1, static_cast<char>(202))), 
  Token::Terminator(string(1, static_cast<char>(203))), 
  Token::Terminator(string(1, static_cast<char>(204))), 
  Token::Terminator(string(1, static_cast<char>(205))), 
  Token::Terminator(string(1, static_cast<char>(206))), 
  Token::Terminator(string(1, static_cast<char>(207))), 
  Token::Terminator(string(1, static_cast<char>(208))), 
  Token::Terminator(string(1, static_cast<char>(209))), 
  Token::Terminator(string(1, static_cast<char>(210))), 
  Token::Terminator(string(1, static_cast<char>(211))), 
  Token::Terminator(string(1, static_cast<char>(212))), 
  Token::Terminator(string(1, static_cast<char>(213))), 
  Token::Terminator(string(1, static_cast<char>(214))), 
  Token::Terminator(string(1, static_cast<char>(215))), 
  Token::Terminator(string(1, static_cast<char>(216))), 
  Token::Terminator(string(1, static_cast<char>(217))), 
  Token::Terminator(string(1, static_cast<char>(218))), 
  Token::Terminator(string(1, static_cast<char>(219))), 
  Token::Terminator(string(1, static_cast<char>(220))), 
  Token::Terminator(string(1, static_cast<char>(221))), 
  Token::Terminator(string(1, static_cast<char>(222))), 
  Token::Terminator(string(1, static_cast<char>(223))), 
  Token::Terminator(string(1, static_cast<char>(224))), 
  Token::Terminator(string(1, static_cast<char>(225))), 
  Token::Terminator(string(1, static_cast<char>(226))), 
  Token::Terminator(string(1, static_cast<char>(227))), 
  Token::Terminator(string(1, static_cast<char>(228))), 
  Token::Terminator(string(1, static_cast<char>(229))), 
  Token::Terminator(string(1, static_cast<char>(230))), 
  Token::Terminator(string(1, static_cast<char>(231))), 
  Token::Terminator(string(1, static_cast<char>(232))), 
  Token::Terminator(string(1, static_cast<char>(233))), 
  Token::Terminator(string(1, static_cast<char>(234))), 
  Token::Terminator(string(1, static_cast<char>(235))), 
  Token::Terminator(string(1, static_cast<char>(236))), 
  Token::Terminator(string(1, static_cast<char>(237))), 
  Token::Terminator(string(1, static_cast<char>(238))), 
  Token::Terminator(string(1, static_cast<char>(239))), 
  Token::Terminator(string(1, static_cast<char>(240))), 
  Token::Terminator(string(1, static_cast<char>(241))), 
  Token::Terminator(string(1, static_cast<char>(242))), 
  Token::Terminator(string(1, static_cast<char>(243))), 
  Token::Terminator(string(1, static_cast<char>(244))), 
  Token::Terminator(string(1, static_cast<char>(245))), 
  Token::Terminator(string(1, static_cast<char>(246))), 
  Token::Terminator(string(1, static_cast<char>(247))), 
  Token::Terminator(string(1, static_cast<char>(248))), 
  Token::Terminator(string(1, static_cast<char>(249))), 
  Token::Terminator(string(1, static_cast<char>(250))), 
  Token::Terminator(string(1, static_cast<char>(251))), 
  Token::Terminator(string(1, static_cast<char>(252))), 
  Token::Terminator(string(1, static_cast<char>(253))), 
  Token::Terminator(string(1, static_cast<char>(254))), 
  Token::Terminator(string(1, static_cast<char>(255))), 
  //@variable
  Token::Terminator("ADD_ASSIGN"), // 256
  Token::Terminator("AND_ASSIGN"), // 257
  Token::Terminator("AND_OP"), // 258
  Token::Terminator("AUTO"), // 259
  Token::Terminator("BOOL"), // 260
  Token::Terminator("BREAK"), // 261
  Token::Terminator("CASE"), // 262
  Token::Terminator("CHAR"), // 263
  Token::Terminator("COMPLEX"), // 264
  Token::Terminator("CONST"), // 265
  Token::Terminator("CONSTANT"), // 266
  Token::Terminator("CONTINUE"), // 267
  Token::Terminator("DEC_OP"), // 268
  Token::Terminator("DEFAULT"), // 269
  Token::Terminator("DIV_ASSIGN"), // 270
  Token::Terminator("DO"), // 271
  Token::Terminator("DOUBLE"), // 272
  Token::Terminator("ELLIPSIS"), // 273
  Token::Terminator("ELSE"), // 274
  Token::Terminator("ENUM"), // 275
  Token::Terminator("EQ_OP"), // 276
  Token::Terminator("EXTERN"), // 277
  Token::Terminator("FLOAT"), // 278
  Token::Terminator("FOR"), // 279
  Token::Terminator("GE_OP"), // 280
  Token::Terminator("GOTO"), // 281
  Token::Terminator("IDENTIFIER"), // 282
  Token::Terminator("IF"), // 283
  Token::Terminator("IMAGINARY"), // 284
  Token::Terminator("INC_OP"), // 285
  Token::Terminator("INLINE"), // 286
  Token::Terminator("INT"), // 287
  Token::Terminator("LEFT_ASSIGN"), // 288
  Token::Terminator("LEFT_OP"), // 289
  Token::Terminator("LE_OP"), // 290
  Token::Terminator("LONG"), // 291
  Token::Terminator("MOD_ASSIGN"), // 292
  Token::Terminator("MUL_ASSIGN"), // 293
  Token::Terminator("NE_OP"), // 294
  Token::Terminator("OR_ASSIGN"), // 295
  Token::Terminator("OR_OP"), // 296
  Token::Terminator("PTR_OP"), // 297
  Token::Terminator("REGISTER"), // 298
  Token::Terminator("RESTRICT"), // 299
  Token::Terminator("RETURN"), // 300
  Token::Terminator("RIGHT_ASSIGN"), // 301
  Token::Terminator("RIGHT_OP"), // 302
  Token::Terminator("SHORT"), // 303
  Token::Terminator("SIGNED"), // 304
  Token::Terminator("SIZEOF"), // 305
  Token::Terminator("STATIC"), // 306
  Token::Terminator("STRING_LITERAL"), // 307
  Token::Terminator("STRUCT"), // 308
  Token::Terminator("SUB_ASSIGN"), // 309
  Token::Terminator("SWITCH"), // 310
  Token::Terminator("TYPEDEF"), // 311
  Token::Terminator("TYPE_NAME"), // 312
  Token::Terminator("UNION"), // 313
  Token::Terminator("UNSIGNED"), // 314
  Token::Terminator("VOID"), // 315
  Token::Terminator("VOLATILE"), // 316
  Token::Terminator("WHILE"), // 317
  Token::Terminator("XOR_ASSIGN"), // 318
  Token::NonTerminator("abstract_declarator"), // 319
  Token::NonTerminator("additive_expression"), // 320
  Token::NonTerminator("and_expression"), // 321
  Token::NonTerminator("argument_expression_list"), // 322
  Token::NonTerminator("assignment_expression"), // 323
  Token::NonTerminator("assignment_operator"), // 324
  Token::NonTerminator("block_item"), // 325
  Token::NonTerminator("block_item_list"), // 326
  Token::NonTerminator("cast_expression"), // 327
  Token::NonTerminator("compound_statement"), // 328
  Token::NonTerminator("conditional_expression"), // 329
  Token::NonTerminator("constant_expression"), // 330
  Token::NonTerminator("declaration"), // 331
  Token::NonTerminator("declaration_list"), // 332
  Token::NonTerminator("declaration_specifiers"), // 333
  Token::NonTerminator("declarator"), // 334
  Token::NonTerminator("designation"), // 335
  Token::NonTerminator("designator"), // 336
  Token::NonTerminator("designator_list"), // 337
  Token::NonTerminator("direct_abstract_declarator"), // 338
  Token::NonTerminator("direct_declarator"), // 339
  Token::NonTerminator("enum_specifier"), // 340
  Token::NonTerminator("enumerator"), // 341
  Token::NonTerminator("enumerator_list"), // 342
  Token::NonTerminator("equality_expression"), // 343
  Token::NonTerminator("exclusive_or_expression"), // 344
  Token::NonTerminator("expression"), // 345
  Token::NonTerminator("expression_statement"), // 346
  Token::NonTerminator("external_declaration"), // 347
  Token::NonTerminator("function_definition"), // 348
  Token::NonTerminator("function_specifier"), // 349
  Token::NonTerminator("identifier_list"), // 350
  Token::NonTerminator("inclusive_or_expression"), // 351
  Token::NonTerminator("init_declarator"), // 352
  Token::NonTerminator("init_declarator_list"), // 353
  Token::NonTerminator("initializer"), // 354
  Token::NonTerminator("initializer_list"), // 355
  Token::NonTerminator("iteration_statement"), // 356
  Token::NonTerminator("jump_statement"), // 357
  Token::NonTerminator("labeled_statement"), // 358
  Token::NonTerminator("logical_and_expression"), // 359
  Token::NonTerminator("logical_or_expression"), // 360
  Token::NonTerminator("multiplicative_expression"), // 361
  Token::NonTerminator("parameter_declaration"), // 362
  Token::NonTerminator("parameter_list"), // 363
  Token::NonTerminator("parameter_type_list"), // 364
  Token::NonTerminator("pointer"), // 365
  Token::NonTerminator("postfix_expression"), // 366
  Token::NonTerminator("primary_expression"), // 367
  Token::NonTerminator("relational_expression"), // 368
  Token::NonTerminator("selection_statement"), // 369
  Token::NonTerminator("shift_expression"), // 370
  Token::NonTerminator("specifier_qualifier_list"), // 371
  Token::NonTerminator("statement"), // 372
  Token::NonTerminator("storage_class_specifier"), // 373
  Token::NonTerminator("struct_declaration"), // 374
  Token::NonTerminator("struct_declaration_list"), // 375
  Token::NonTerminator("struct_declarator"), // 376
  Token::NonTerminator("struct_declarator_list"), // 377
  Token::NonTerminator("struct_or_union"), // 378
  Token::NonTerminator("struct_or_union_specifier"), // 379
  Token::NonTerminator("translation_unit"), // 380
  Token::NonTerminator("type_name"), // 381
  Token::NonTerminator("type_qualifier"), // 382
  Token::NonTerminator("type_qualifier_list"), // 383
  Token::NonTerminator("type_specifier"), // 384
  Token::NonTerminator("unary_expression"), // 385
  Token::NonTerminator("unary_operator"), // 386
};

//@variable
auto &start_syntax_token = syntax_tokens[translation_unit];

/* section 4 */
// syntax
//@variable
vector<Production> productions = {
  // primary_expression : IDENTIFIER ;
  Production(syntax_tokens[primary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER]), 
  // primary_expression : CONSTANT ;
  Production(syntax_tokens[primary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[CONSTANT]), 
  // primary_expression : STRING_LITERAL ;
  Production(syntax_tokens[primary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[STRING_LITERAL]), 
  // primary_expression : '(' expression ')' ;
  Production(syntax_tokens[primary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[expression])(syntax_tokens[')']), 
  // postfix_expression : primary_expression ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[primary_expression]), 
  // postfix_expression : postfix_expression '[' expression ']' ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens['['])(syntax_tokens[expression])(syntax_tokens[']']), 
  // postfix_expression : postfix_expression '(' ')' ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens['('])(syntax_tokens[')']), 
  // postfix_expression : postfix_expression '(' argument_expression_list ')' ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens['('])(syntax_tokens[argument_expression_list])(syntax_tokens[')']), 
  // postfix_expression : postfix_expression '.' IDENTIFIER ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens['.'])(syntax_tokens[IDENTIFIER]), 
  // postfix_expression : postfix_expression PTR_OP IDENTIFIER ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens[PTR_OP])(syntax_tokens[IDENTIFIER]), 
  // postfix_expression : postfix_expression INC_OP ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens[INC_OP]), 
  // postfix_expression : postfix_expression DEC_OP ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression])(syntax_tokens[DEC_OP]), 
  // postfix_expression : '(' type_name ')' '{' initializer_list '}' ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[type_name])(syntax_tokens[')'])(syntax_tokens['{'])(syntax_tokens[initializer_list])(syntax_tokens['}']), 
  // postfix_expression : '(' type_name ')' '{' initializer_list ',' '}' ;
  Production(syntax_tokens[postfix_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[type_name])(syntax_tokens[')'])(syntax_tokens['{'])(syntax_tokens[initializer_list])(syntax_tokens[','])(syntax_tokens['}']), 
  // argument_expression_list : assignment_expression ;
  Production(syntax_tokens[argument_expression_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[assignment_expression]), 
  // argument_expression_list : argument_expression_list ',' assignment_expression ;
  Production(syntax_tokens[argument_expression_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[argument_expression_list])(syntax_tokens[','])(syntax_tokens[assignment_expression]), 
  // unary_expression : postfix_expression ;
  Production(syntax_tokens[unary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[postfix_expression]), 
  // unary_expression : INC_OP unary_expression ;
  Production(syntax_tokens[unary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[INC_OP])(syntax_tokens[unary_expression]), 
  // unary_expression : DEC_OP unary_expression ;
  Production(syntax_tokens[unary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[DEC_OP])(syntax_tokens[unary_expression]), 
  // unary_expression : unary_operator cast_expression ;
  Production(syntax_tokens[unary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[unary_operator])(syntax_tokens[cast_expression]), 
  // unary_expression : SIZEOF unary_expression ;
  Production(syntax_tokens[unary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[SIZEOF])(syntax_tokens[unary_expression]), 
  // unary_expression : SIZEOF '(' type_name ')' ;
  Production(syntax_tokens[unary_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[SIZEOF])(syntax_tokens['('])(syntax_tokens[type_name])(syntax_tokens[')']), 
  // unary_operator : '&' ;
  Production(syntax_tokens[unary_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['&']), 
  // unary_operator : '*' ;
  Production(syntax_tokens[unary_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['*']), 
  // unary_operator : '+' ;
  Production(syntax_tokens[unary_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['+']), 
  // unary_operator : '-' ;
  Production(syntax_tokens[unary_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['-']), 
  // unary_operator : '~' ;
  Production(syntax_tokens[unary_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['~']), 
  // unary_operator : '!' ;
  Production(syntax_tokens[unary_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['!']), 
  // cast_expression : unary_expression ;
  Production(syntax_tokens[cast_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[unary_expression]), 
  // cast_expression : '(' type_name ')' cast_expression ;
  Production(syntax_tokens[cast_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[type_name])(syntax_tokens[')'])(syntax_tokens[cast_expression]), 
  // multiplicative_expression : cast_expression ;
  Production(syntax_tokens[multiplicative_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[cast_expression]), 
  // multiplicative_expression : multiplicative_expression '*' cast_expression ;
  Production(syntax_tokens[multiplicative_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[multiplicative_expression])(syntax_tokens['*'])(syntax_tokens[cast_expression]), 
  // multiplicative_expression : multiplicative_expression '/' cast_expression ;
  Production(syntax_tokens[multiplicative_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[multiplicative_expression])(syntax_tokens['/'])(syntax_tokens[cast_expression]), 
  // multiplicative_expression : multiplicative_expression '%' cast_expression ;
  Production(syntax_tokens[multiplicative_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[multiplicative_expression])(syntax_tokens['%'])(syntax_tokens[cast_expression]), 
  // additive_expression : multiplicative_expression ;
  Production(syntax_tokens[additive_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[multiplicative_expression]), 
  // additive_expression : additive_expression '+' multiplicative_expression ;
  Production(syntax_tokens[additive_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[additive_expression])(syntax_tokens['+'])(syntax_tokens[multiplicative_expression]), 
  // additive_expression : additive_expression '-' multiplicative_expression ;
  Production(syntax_tokens[additive_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[additive_expression])(syntax_tokens['-'])(syntax_tokens[multiplicative_expression]), 
  // shift_expression : additive_expression ;
  Production(syntax_tokens[shift_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[additive_expression]), 
  // shift_expression : shift_expression LEFT_OP additive_expression ;
  Production(syntax_tokens[shift_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[shift_expression])(syntax_tokens[LEFT_OP])(syntax_tokens[additive_expression]), 
  // shift_expression : shift_expression RIGHT_OP additive_expression ;
  Production(syntax_tokens[shift_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[shift_expression])(syntax_tokens[RIGHT_OP])(syntax_tokens[additive_expression]), 
  // relational_expression : shift_expression ;
  Production(syntax_tokens[relational_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[shift_expression]), 
  // relational_expression : relational_expression '<' shift_expression ;
  Production(syntax_tokens[relational_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[relational_expression])(syntax_tokens['<'])(syntax_tokens[shift_expression]), 
  // relational_expression : relational_expression '>' shift_expression ;
  Production(syntax_tokens[relational_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[relational_expression])(syntax_tokens['>'])(syntax_tokens[shift_expression]), 
  // relational_expression : relational_expression LE_OP shift_expression ;
  Production(syntax_tokens[relational_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[relational_expression])(syntax_tokens[LE_OP])(syntax_tokens[shift_expression]), 
  // relational_expression : relational_expression GE_OP shift_expression ;
  Production(syntax_tokens[relational_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[relational_expression])(syntax_tokens[GE_OP])(syntax_tokens[shift_expression]), 
  // equality_expression : relational_expression ;
  Production(syntax_tokens[equality_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[relational_expression]), 
  // equality_expression : equality_expression EQ_OP relational_expression ;
  Production(syntax_tokens[equality_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[equality_expression])(syntax_tokens[EQ_OP])(syntax_tokens[relational_expression]), 
  // equality_expression : equality_expression NE_OP relational_expression ;
  Production(syntax_tokens[equality_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[equality_expression])(syntax_tokens[NE_OP])(syntax_tokens[relational_expression]), 
  // and_expression : equality_expression ;
  Production(syntax_tokens[and_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[equality_expression]), 
  // and_expression : and_expression '&' equality_expression ;
  Production(syntax_tokens[and_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[and_expression])(syntax_tokens['&'])(syntax_tokens[equality_expression]), 
  // exclusive_or_expression : and_expression ;
  Production(syntax_tokens[exclusive_or_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[and_expression]), 
  // exclusive_or_expression : exclusive_or_expression '^' and_expression ;
  Production(syntax_tokens[exclusive_or_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[exclusive_or_expression])(syntax_tokens['^'])(syntax_tokens[and_expression]), 
  // inclusive_or_expression : exclusive_or_expression ;
  Production(syntax_tokens[inclusive_or_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[exclusive_or_expression]), 
  // inclusive_or_expression : inclusive_or_expression '|' exclusive_or_expression ;
  Production(syntax_tokens[inclusive_or_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[inclusive_or_expression])(syntax_tokens['|'])(syntax_tokens[exclusive_or_expression]), 
  // logical_and_expression : inclusive_or_expression ;
  Production(syntax_tokens[logical_and_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[inclusive_or_expression]), 
  // logical_and_expression : logical_and_expression AND_OP inclusive_or_expression ;
  Production(syntax_tokens[logical_and_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[logical_and_expression])(syntax_tokens[AND_OP])(syntax_tokens[inclusive_or_expression]), 
  // logical_or_expression : logical_and_expression ;
  Production(syntax_tokens[logical_or_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[logical_and_expression]), 
  // logical_or_expression : logical_or_expression OR_OP logical_and_expression ;
  Production(syntax_tokens[logical_or_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[logical_or_expression])(syntax_tokens[OR_OP])(syntax_tokens[logical_and_expression]), 
  // conditional_expression : logical_or_expression ;
  Production(syntax_tokens[conditional_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[logical_or_expression]), 
  // conditional_expression : logical_or_expression '?' expression ':' conditional_expression ;
  Production(syntax_tokens[conditional_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[logical_or_expression])(syntax_tokens['?'])(syntax_tokens[expression])(syntax_tokens[':'])(syntax_tokens[conditional_expression]), 
  // assignment_expression : conditional_expression ;
  Production(syntax_tokens[assignment_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[conditional_expression]), 
  // assignment_expression : unary_expression assignment_operator assignment_expression ;
  Production(syntax_tokens[assignment_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[unary_expression])(syntax_tokens[assignment_operator])(syntax_tokens[assignment_expression]), 
  // assignment_operator : '=' ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['=']), 
  // assignment_operator : MUL_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[MUL_ASSIGN]), 
  // assignment_operator : DIV_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[DIV_ASSIGN]), 
  // assignment_operator : MOD_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[MOD_ASSIGN]), 
  // assignment_operator : ADD_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[ADD_ASSIGN]), 
  // assignment_operator : SUB_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[SUB_ASSIGN]), 
  // assignment_operator : LEFT_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[LEFT_ASSIGN]), 
  // assignment_operator : RIGHT_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[RIGHT_ASSIGN]), 
  // assignment_operator : AND_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[AND_ASSIGN]), 
  // assignment_operator : XOR_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[XOR_ASSIGN]), 
  // assignment_operator : OR_ASSIGN ;
  Production(syntax_tokens[assignment_operator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[OR_ASSIGN]), 
  // expression : assignment_expression ;
  Production(syntax_tokens[expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[assignment_expression]), 
  // expression : expression ',' assignment_expression ;
  Production(syntax_tokens[expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[expression])(syntax_tokens[','])(syntax_tokens[assignment_expression]), 
  // constant_expression : conditional_expression ;
  Production(syntax_tokens[constant_expression], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[conditional_expression]), 
  // declaration : declaration_specifiers ';' ;
  Production(syntax_tokens[declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[';']), 
  // declaration : declaration_specifiers init_declarator_list ';' ;
  Production(syntax_tokens[declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[init_declarator_list])(syntax_tokens[';']), 
  // declaration_specifiers : storage_class_specifier ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[storage_class_specifier]), 
  // declaration_specifiers : storage_class_specifier declaration_specifiers ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[storage_class_specifier])(syntax_tokens[declaration_specifiers]), 
  // declaration_specifiers : type_specifier ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_specifier]), 
  // declaration_specifiers : type_specifier declaration_specifiers ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_specifier])(syntax_tokens[declaration_specifiers]), 
  // declaration_specifiers : type_qualifier ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_qualifier]), 
  // declaration_specifiers : type_qualifier declaration_specifiers ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_qualifier])(syntax_tokens[declaration_specifiers]), 
  // declaration_specifiers : function_specifier ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[function_specifier]), 
  // declaration_specifiers : function_specifier declaration_specifiers ;
  Production(syntax_tokens[declaration_specifiers], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[function_specifier])(syntax_tokens[declaration_specifiers]), 
  // init_declarator_list : init_declarator ;
  Production(syntax_tokens[init_declarator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[init_declarator]), 
  // init_declarator_list : init_declarator_list ',' init_declarator ;
  Production(syntax_tokens[init_declarator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[init_declarator_list])(syntax_tokens[','])(syntax_tokens[init_declarator]), 
  // init_declarator : declarator ;
  Production(syntax_tokens[init_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declarator]), 
  // init_declarator : declarator '=' initializer ;
  Production(syntax_tokens[init_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declarator])(syntax_tokens['='])(syntax_tokens[initializer]), 
  // storage_class_specifier : TYPEDEF ;
  Production(syntax_tokens[storage_class_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[TYPEDEF]), 
  // storage_class_specifier : EXTERN ;
  Production(syntax_tokens[storage_class_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[EXTERN]), 
  // storage_class_specifier : STATIC ;
  Production(syntax_tokens[storage_class_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[STATIC]), 
  // storage_class_specifier : AUTO ;
  Production(syntax_tokens[storage_class_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[AUTO]), 
  // storage_class_specifier : REGISTER ;
  Production(syntax_tokens[storage_class_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[REGISTER]), 
  // type_specifier : VOID ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[VOID]), 
  // type_specifier : CHAR ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[CHAR]), 
  // type_specifier : SHORT ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[SHORT]), 
  // type_specifier : INT ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[INT]), 
  // type_specifier : LONG ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[LONG]), 
  // type_specifier : FLOAT ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[FLOAT]), 
  // type_specifier : DOUBLE ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[DOUBLE]), 
  // type_specifier : SIGNED ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[SIGNED]), 
  // type_specifier : UNSIGNED ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[UNSIGNED]), 
  // type_specifier : BOOL ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[BOOL]), 
  // type_specifier : COMPLEX ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[COMPLEX]), 
  // type_specifier : IMAGINARY ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IMAGINARY]), 
  // type_specifier : struct_or_union_specifier ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_or_union_specifier]), 
  // type_specifier : enum_specifier ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[enum_specifier]), 
  // type_specifier : TYPE_NAME ;
  Production(syntax_tokens[type_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[TYPE_NAME]), 
  // struct_or_union_specifier : struct_or_union IDENTIFIER '{' struct_declaration_list '}' ;
  Production(syntax_tokens[struct_or_union_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_or_union])(syntax_tokens[IDENTIFIER])(syntax_tokens['{'])(syntax_tokens[struct_declaration_list])(syntax_tokens['}']), 
  // struct_or_union_specifier : struct_or_union '{' struct_declaration_list '}' ;
  Production(syntax_tokens[struct_or_union_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_or_union])(syntax_tokens['{'])(syntax_tokens[struct_declaration_list])(syntax_tokens['}']), 
  // struct_or_union_specifier : struct_or_union IDENTIFIER ;
  Production(syntax_tokens[struct_or_union_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_or_union])(syntax_tokens[IDENTIFIER]), 
  // struct_or_union : STRUCT ;
  Production(syntax_tokens[struct_or_union], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[STRUCT]), 
  // struct_or_union : UNION ;
  Production(syntax_tokens[struct_or_union], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[UNION]), 
  // struct_declaration_list : struct_declaration ;
  Production(syntax_tokens[struct_declaration_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_declaration]), 
  // struct_declaration_list : struct_declaration_list struct_declaration ;
  Production(syntax_tokens[struct_declaration_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_declaration_list])(syntax_tokens[struct_declaration]), 
  // struct_declaration : specifier_qualifier_list struct_declarator_list ';' ;
  Production(syntax_tokens[struct_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[specifier_qualifier_list])(syntax_tokens[struct_declarator_list])(syntax_tokens[';']), 
  // specifier_qualifier_list : type_specifier specifier_qualifier_list ;
  Production(syntax_tokens[specifier_qualifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_specifier])(syntax_tokens[specifier_qualifier_list]), 
  // specifier_qualifier_list : type_specifier ;
  Production(syntax_tokens[specifier_qualifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_specifier]), 
  // specifier_qualifier_list : type_qualifier specifier_qualifier_list ;
  Production(syntax_tokens[specifier_qualifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_qualifier])(syntax_tokens[specifier_qualifier_list]), 
  // specifier_qualifier_list : type_qualifier ;
  Production(syntax_tokens[specifier_qualifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_qualifier]), 
  // struct_declarator_list : struct_declarator ;
  Production(syntax_tokens[struct_declarator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_declarator]), 
  // struct_declarator_list : struct_declarator_list ',' struct_declarator ;
  Production(syntax_tokens[struct_declarator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[struct_declarator_list])(syntax_tokens[','])(syntax_tokens[struct_declarator]), 
  // struct_declarator : declarator ;
  Production(syntax_tokens[struct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declarator]), 
  // struct_declarator : ':' constant_expression ;
  Production(syntax_tokens[struct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[':'])(syntax_tokens[constant_expression]), 
  // struct_declarator : declarator ':' constant_expression ;
  Production(syntax_tokens[struct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declarator])(syntax_tokens[':'])(syntax_tokens[constant_expression]), 
  // enum_specifier : ENUM '{' enumerator_list '}' ;
  Production(syntax_tokens[enum_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[ENUM])(syntax_tokens['{'])(syntax_tokens[enumerator_list])(syntax_tokens['}']), 
  // enum_specifier : ENUM IDENTIFIER '{' enumerator_list '}' ;
  Production(syntax_tokens[enum_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[ENUM])(syntax_tokens[IDENTIFIER])(syntax_tokens['{'])(syntax_tokens[enumerator_list])(syntax_tokens['}']), 
  // enum_specifier : ENUM '{' enumerator_list ',' '}' ;
  Production(syntax_tokens[enum_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[ENUM])(syntax_tokens['{'])(syntax_tokens[enumerator_list])(syntax_tokens[','])(syntax_tokens['}']), 
  // enum_specifier : ENUM IDENTIFIER '{' enumerator_list ',' '}' ;
  Production(syntax_tokens[enum_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[ENUM])(syntax_tokens[IDENTIFIER])(syntax_tokens['{'])(syntax_tokens[enumerator_list])(syntax_tokens[','])(syntax_tokens['}']), 
  // enum_specifier : ENUM IDENTIFIER ;
  Production(syntax_tokens[enum_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[ENUM])(syntax_tokens[IDENTIFIER]), 
  // enumerator_list : enumerator ;
  Production(syntax_tokens[enumerator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[enumerator]), 
  // enumerator_list : enumerator_list ',' enumerator ;
  Production(syntax_tokens[enumerator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[enumerator_list])(syntax_tokens[','])(syntax_tokens[enumerator]), 
  // enumerator : IDENTIFIER ;
  Production(syntax_tokens[enumerator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER]), 
  // enumerator : IDENTIFIER '=' constant_expression ;
  Production(syntax_tokens[enumerator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER])(syntax_tokens['='])(syntax_tokens[constant_expression]), 
  // type_qualifier : CONST ;
  Production(syntax_tokens[type_qualifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[CONST]), 
  // type_qualifier : RESTRICT ;
  Production(syntax_tokens[type_qualifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[RESTRICT]), 
  // type_qualifier : VOLATILE ;
  Production(syntax_tokens[type_qualifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[VOLATILE]), 
  // function_specifier : INLINE ;
  Production(syntax_tokens[function_specifier], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[INLINE]), 
  // declarator : pointer direct_declarator ;
  Production(syntax_tokens[declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[pointer])(syntax_tokens[direct_declarator]), 
  // declarator : direct_declarator ;
  Production(syntax_tokens[declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator]), 
  // direct_declarator : IDENTIFIER ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER]), 
  // direct_declarator : '(' declarator ')' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[declarator])(syntax_tokens[')']), 
  // direct_declarator : direct_declarator '[' type_qualifier_list assignment_expression ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[type_qualifier_list])(syntax_tokens[assignment_expression])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' type_qualifier_list ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[type_qualifier_list])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' assignment_expression ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[assignment_expression])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' STATIC type_qualifier_list assignment_expression ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[STATIC])(syntax_tokens[type_qualifier_list])(syntax_tokens[assignment_expression])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' type_qualifier_list STATIC assignment_expression ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[type_qualifier_list])(syntax_tokens[STATIC])(syntax_tokens[assignment_expression])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' type_qualifier_list '*' ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[type_qualifier_list])(syntax_tokens['*'])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' '*' ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens['*'])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '[' ']' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['['])(syntax_tokens[']']), 
  // direct_declarator : direct_declarator '(' parameter_type_list ')' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['('])(syntax_tokens[parameter_type_list])(syntax_tokens[')']), 
  // direct_declarator : direct_declarator '(' identifier_list ')' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['('])(syntax_tokens[identifier_list])(syntax_tokens[')']), 
  // direct_declarator : direct_declarator '(' ')' ;
  Production(syntax_tokens[direct_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_declarator])(syntax_tokens['('])(syntax_tokens[')']), 
  // pointer : '*' ;
  Production(syntax_tokens[pointer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['*']), 
  // pointer : '*' type_qualifier_list ;
  Production(syntax_tokens[pointer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['*'])(syntax_tokens[type_qualifier_list]), 
  // pointer : '*' pointer ;
  Production(syntax_tokens[pointer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['*'])(syntax_tokens[pointer]), 
  // pointer : '*' type_qualifier_list pointer ;
  Production(syntax_tokens[pointer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['*'])(syntax_tokens[type_qualifier_list])(syntax_tokens[pointer]), 
  // type_qualifier_list : type_qualifier ;
  Production(syntax_tokens[type_qualifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_qualifier]), 
  // type_qualifier_list : type_qualifier_list type_qualifier ;
  Production(syntax_tokens[type_qualifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[type_qualifier_list])(syntax_tokens[type_qualifier]), 
  // parameter_type_list : parameter_list ;
  Production(syntax_tokens[parameter_type_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[parameter_list]), 
  // parameter_type_list : parameter_list ',' ELLIPSIS ;
  Production(syntax_tokens[parameter_type_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[parameter_list])(syntax_tokens[','])(syntax_tokens[ELLIPSIS]), 
  // parameter_list : parameter_declaration ;
  Production(syntax_tokens[parameter_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[parameter_declaration]), 
  // parameter_list : parameter_list ',' parameter_declaration ;
  Production(syntax_tokens[parameter_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[parameter_list])(syntax_tokens[','])(syntax_tokens[parameter_declaration]), 
  // parameter_declaration : declaration_specifiers declarator ;
  Production(syntax_tokens[parameter_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[declarator]), 
  // parameter_declaration : declaration_specifiers abstract_declarator ;
  Production(syntax_tokens[parameter_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[abstract_declarator]), 
  // parameter_declaration : declaration_specifiers ;
  Production(syntax_tokens[parameter_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers]), 
  // identifier_list : IDENTIFIER ;
  Production(syntax_tokens[identifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER]), 
  // identifier_list : identifier_list ',' IDENTIFIER ;
  Production(syntax_tokens[identifier_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[identifier_list])(syntax_tokens[','])(syntax_tokens[IDENTIFIER]), 
  // type_name : specifier_qualifier_list ;
  Production(syntax_tokens[type_name], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[specifier_qualifier_list]), 
  // type_name : specifier_qualifier_list abstract_declarator ;
  Production(syntax_tokens[type_name], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[specifier_qualifier_list])(syntax_tokens[abstract_declarator]), 
  // abstract_declarator : pointer ;
  Production(syntax_tokens[abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[pointer]), 
  // abstract_declarator : direct_abstract_declarator ;
  Production(syntax_tokens[abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_abstract_declarator]), 
  // abstract_declarator : pointer direct_abstract_declarator ;
  Production(syntax_tokens[abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[pointer])(syntax_tokens[direct_abstract_declarator]), 
  // direct_abstract_declarator : '(' abstract_declarator ')' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[abstract_declarator])(syntax_tokens[')']), 
  // direct_abstract_declarator : '[' ']' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['['])(syntax_tokens[']']), 
  // direct_abstract_declarator : '[' assignment_expression ']' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['['])(syntax_tokens[assignment_expression])(syntax_tokens[']']), 
  // direct_abstract_declarator : direct_abstract_declarator '[' ']' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_abstract_declarator])(syntax_tokens['['])(syntax_tokens[']']), 
  // direct_abstract_declarator : direct_abstract_declarator '[' assignment_expression ']' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_abstract_declarator])(syntax_tokens['['])(syntax_tokens[assignment_expression])(syntax_tokens[']']), 
  // direct_abstract_declarator : '[' '*' ']' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['['])(syntax_tokens['*'])(syntax_tokens[']']), 
  // direct_abstract_declarator : direct_abstract_declarator '[' '*' ']' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_abstract_declarator])(syntax_tokens['['])(syntax_tokens['*'])(syntax_tokens[']']), 
  // direct_abstract_declarator : '(' ')' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[')']), 
  // direct_abstract_declarator : '(' parameter_type_list ')' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['('])(syntax_tokens[parameter_type_list])(syntax_tokens[')']), 
  // direct_abstract_declarator : direct_abstract_declarator '(' ')' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_abstract_declarator])(syntax_tokens['('])(syntax_tokens[')']), 
  // direct_abstract_declarator : direct_abstract_declarator '(' parameter_type_list ')' ;
  Production(syntax_tokens[direct_abstract_declarator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[direct_abstract_declarator])(syntax_tokens['('])(syntax_tokens[parameter_type_list])(syntax_tokens[')']), 
  // initializer : assignment_expression ;
  Production(syntax_tokens[initializer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[assignment_expression]), 
  // initializer : '{' initializer_list '}' ;
  Production(syntax_tokens[initializer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['{'])(syntax_tokens[initializer_list])(syntax_tokens['}']), 
  // initializer : '{' initializer_list ',' '}' ;
  Production(syntax_tokens[initializer], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['{'])(syntax_tokens[initializer_list])(syntax_tokens[','])(syntax_tokens['}']), 
  // initializer_list : initializer ;
  Production(syntax_tokens[initializer_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[initializer]), 
  // initializer_list : designation initializer ;
  Production(syntax_tokens[initializer_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[designation])(syntax_tokens[initializer]), 
  // initializer_list : initializer_list ',' initializer ;
  Production(syntax_tokens[initializer_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[initializer_list])(syntax_tokens[','])(syntax_tokens[initializer]), 
  // initializer_list : initializer_list ',' designation initializer ;
  Production(syntax_tokens[initializer_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[initializer_list])(syntax_tokens[','])(syntax_tokens[designation])(syntax_tokens[initializer]), 
  // designation : designator_list '=' ;
  Production(syntax_tokens[designation], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[designator_list])(syntax_tokens['=']), 
  // designator_list : designator ;
  Production(syntax_tokens[designator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[designator]), 
  // designator_list : designator_list designator ;
  Production(syntax_tokens[designator_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[designator_list])(syntax_tokens[designator]), 
  // designator : '[' constant_expression ']' ;
  Production(syntax_tokens[designator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['['])(syntax_tokens[constant_expression])(syntax_tokens[']']), 
  // designator : '.' IDENTIFIER ;
  Production(syntax_tokens[designator], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['.'])(syntax_tokens[IDENTIFIER]), 
  // statement : labeled_statement ;
  Production(syntax_tokens[statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[labeled_statement]), 
  // statement : compound_statement ;
  Production(syntax_tokens[statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[compound_statement]), 
  // statement : expression_statement ;
  Production(syntax_tokens[statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[expression_statement]), 
  // statement : selection_statement ;
  Production(syntax_tokens[statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[selection_statement]), 
  // statement : iteration_statement ;
  Production(syntax_tokens[statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[iteration_statement]), 
  // statement : jump_statement ;
  Production(syntax_tokens[statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[jump_statement]), 
  // labeled_statement : IDENTIFIER ':' statement ;
  Production(syntax_tokens[labeled_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IDENTIFIER])(syntax_tokens[':'])(syntax_tokens[statement]), 
  // labeled_statement : CASE constant_expression ':' statement ;
  Production(syntax_tokens[labeled_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[CASE])(syntax_tokens[constant_expression])(syntax_tokens[':'])(syntax_tokens[statement]), 
  // labeled_statement : DEFAULT ':' statement ;
  Production(syntax_tokens[labeled_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[DEFAULT])(syntax_tokens[':'])(syntax_tokens[statement]), 
  // compound_statement : '{' '}' ;
  Production(syntax_tokens[compound_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['{'])(syntax_tokens['}']), 
  // compound_statement : '{' block_item_list '}' ;
  Production(syntax_tokens[compound_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens['{'])(syntax_tokens[block_item_list])(syntax_tokens['}']), 
  // block_item_list : block_item ;
  Production(syntax_tokens[block_item_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[block_item]), 
  // block_item_list : block_item_list block_item ;
  Production(syntax_tokens[block_item_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[block_item_list])(syntax_tokens[block_item]), 
  // block_item : declaration ;
  Production(syntax_tokens[block_item], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration]), 
  // block_item : statement ;
  Production(syntax_tokens[block_item], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[statement]), 
  // expression_statement : ';' ;
  Production(syntax_tokens[expression_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[';']), 
  // expression_statement : expression ';' ;
  Production(syntax_tokens[expression_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[expression])(syntax_tokens[';']), 
  // selection_statement : IF '(' expression ')' statement ;
  Production(syntax_tokens[selection_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IF])(syntax_tokens['('])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // selection_statement : IF '(' expression ')' statement ELSE statement ;
  Production(syntax_tokens[selection_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[IF])(syntax_tokens['('])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[statement])(syntax_tokens[ELSE])(syntax_tokens[statement]), 
  // selection_statement : SWITCH '(' expression ')' statement ;
  Production(syntax_tokens[selection_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[SWITCH])(syntax_tokens['('])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // iteration_statement : WHILE '(' expression ')' statement ;
  Production(syntax_tokens[iteration_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[WHILE])(syntax_tokens['('])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // iteration_statement : DO statement WHILE '(' expression ')' ';' ;
  Production(syntax_tokens[iteration_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[DO])(syntax_tokens[statement])(syntax_tokens[WHILE])(syntax_tokens['('])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[';']), 
  // iteration_statement : FOR '(' expression_statement expression_statement ')' statement ;
  Production(syntax_tokens[iteration_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[FOR])(syntax_tokens['('])(syntax_tokens[expression_statement])(syntax_tokens[expression_statement])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // iteration_statement : FOR '(' expression_statement expression_statement expression ')' statement ;
  Production(syntax_tokens[iteration_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[FOR])(syntax_tokens['('])(syntax_tokens[expression_statement])(syntax_tokens[expression_statement])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // iteration_statement : FOR '(' declaration expression_statement ')' statement ;
  Production(syntax_tokens[iteration_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[FOR])(syntax_tokens['('])(syntax_tokens[declaration])(syntax_tokens[expression_statement])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // iteration_statement : FOR '(' declaration expression_statement expression ')' statement ;
  Production(syntax_tokens[iteration_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[FOR])(syntax_tokens['('])(syntax_tokens[declaration])(syntax_tokens[expression_statement])(syntax_tokens[expression])(syntax_tokens[')'])(syntax_tokens[statement]), 
  // jump_statement : GOTO IDENTIFIER ';' ;
  Production(syntax_tokens[jump_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[GOTO])(syntax_tokens[IDENTIFIER])(syntax_tokens[';']), 
  // jump_statement : CONTINUE ';' ;
  Production(syntax_tokens[jump_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[CONTINUE])(syntax_tokens[';']), 
  // jump_statement : BREAK ';' ;
  Production(syntax_tokens[jump_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[BREAK])(syntax_tokens[';']), 
  // jump_statement : RETURN ';' ;
  Production(syntax_tokens[jump_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[RETURN])(syntax_tokens[';']), 
  // jump_statement : RETURN expression ';' ;
  Production(syntax_tokens[jump_statement], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[RETURN])(syntax_tokens[expression])(syntax_tokens[';']), 
  // translation_unit : external_declaration ;
  Production(syntax_tokens[translation_unit], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[external_declaration]), 
  // translation_unit : translation_unit external_declaration ;
  Production(syntax_tokens[translation_unit], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[translation_unit])(syntax_tokens[external_declaration]), 
  // external_declaration : function_definition ;
  Production(syntax_tokens[external_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[function_definition]), 
  // external_declaration : declaration ;
  Production(syntax_tokens[external_declaration], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration]), 
  // function_definition : declaration_specifiers declarator declaration_list compound_statement ;
  Production(syntax_tokens[function_definition], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[declarator])(syntax_tokens[declaration_list])(syntax_tokens[compound_statement]), 
  // function_definition : declaration_specifiers declarator compound_statement ;
  Production(syntax_tokens[function_definition], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_specifiers])(syntax_tokens[declarator])(syntax_tokens[compound_statement]), 
  // declaration_list : declaration ;
  Production(syntax_tokens[declaration_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration]), 
  // declaration_list : declaration_list declaration ;
  Production(syntax_tokens[declaration_list], {[](vector<YYSTATE> &v) {
      // action ...
    }})(syntax_tokens[declaration_list])(syntax_tokens[declaration]), 
};
// lexical
//@variable
vector<Token> lexical_tokens = {
  Token::Terminator(R"((/\*))"), 
  Token::Terminator(R"((//)[^\n\r]*)"), 
  Token::Terminator(R"((auto))"), 
  Token::Terminator(R"((_Bool))"), 
  Token::Terminator(R"((break))"), 
  Token::Terminator(R"((case))"), 
  Token::Terminator(R"((char))"), 
  Token::Terminator(R"((_Complex))"), 
  Token::Terminator(R"((const))"), 
  Token::Terminator(R"((continue))"), 
  Token::Terminator(R"((default))"), 
  Token::Terminator(R"((do))"), 
  Token::Terminator(R"((double))"), 
  Token::Terminator(R"((else))"), 
  Token::Terminator(R"((enum))"), 
  Token::Terminator(R"((extern))"), 
  Token::Terminator(R"((float))"), 
  Token::Terminator(R"((for))"), 
  Token::Terminator(R"((goto))"), 
  Token::Terminator(R"((if))"), 
  Token::Terminator(R"((_Imaginary))"), 
  Token::Terminator(R"((inline))"), 
  Token::Terminator(R"((int))"), 
  Token::Terminator(R"((long))"), 
  Token::Terminator(R"((register))"), 
  Token::Terminator(R"((restrict))"), 
  Token::Terminator(R"((return))"), 
  Token::Terminator(R"((short))"), 
  Token::Terminator(R"((signed))"), 
  Token::Terminator(R"((sizeof))"), 
  Token::Terminator(R"((static))"), 
  Token::Terminator(R"((struct))"), 
  Token::Terminator(R"((switch))"), 
  Token::Terminator(R"((typedef))"), 
  Token::Terminator(R"((union))"), 
  Token::Terminator(R"((unsigned))"), 
  Token::Terminator(R"((void))"), 
  Token::Terminator(R"((volatile))"), 
  Token::Terminator(R"((while))"), 
  Token::Terminator(R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)"), 
  Token::Terminator(R"(0[xX][a-fA-F0-9]+((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)"), 
  Token::Terminator(R"(0[0-7]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)"), 
  Token::Terminator(R"([1-9][0-9]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)"), 
  Token::Terminator(R"(L?'(\\.|[^\\'\n\r])+')"), 
  Token::Terminator(R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)"), 
  Token::Terminator(R"([0-9]*(\.)[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?)"), 
  Token::Terminator(R"([0-9]+(\.)[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?)"), 
  Token::Terminator(R"(0[xX][a-fA-F0-9]+([Pp][+-]?[0-9]+)(f|F|l|L)?)"), 
  Token::Terminator(R"(0[xX][a-fA-F0-9]*(\.)[a-fA-F0-9]+([Pp][+-]?[0-9]+)?(f|F|l|L)?)"), 
  Token::Terminator(R"(0[xX][a-fA-F0-9]+(\.)[a-fA-F0-9]*([Pp][+-]?[0-9]+)?(f|F|l|L)?)"), 
  Token::Terminator(R"(L?"(\\.|[^\\"\n\r])*")"), 
  Token::Terminator(R"((\.\.\.))"), 
  Token::Terminator(R"((>>=))"), 
  Token::Terminator(R"((<<=))"), 
  Token::Terminator(R"((\+=))"), 
  Token::Terminator(R"((-=))"), 
  Token::Terminator(R"((\*=))"), 
  Token::Terminator(R"((/=))"), 
  Token::Terminator(R"((%=))"), 
  Token::Terminator(R"((&=))"), 
  Token::Terminator(R"((\^=))"), 
  Token::Terminator(R"((\|=))"), 
  Token::Terminator(R"((>>))"), 
  Token::Terminator(R"((<<))"), 
  Token::Terminator(R"((\+\+))"), 
  Token::Terminator(R"((--))"), 
  Token::Terminator(R"((->))"), 
  Token::Terminator(R"((&&))"), 
  Token::Terminator(R"((\|\|))"), 
  Token::Terminator(R"((<=))"), 
  Token::Terminator(R"((>=))"), 
  Token::Terminator(R"((==))"), 
  Token::Terminator(R"((!=))"), 
  Token::Terminator(R"((;))"), 
  Token::Terminator(R"((({)|(<%)))"), 
  Token::Terminator(R"(((})|(%>)))"), 
  Token::Terminator(R"((,))"), 
  Token::Terminator(R"((:))"), 
  Token::Terminator(R"((=))"), 
  Token::Terminator(R"((\())"), 
  Token::Terminator(R"((\)))"), 
  Token::Terminator(R"(((\[)|(<:)))"), 
  Token::Terminator(R"(((\])|(:>)))"), 
  Token::Terminator(R"((\.))"), 
  Token::Terminator(R"((&))"), 
  Token::Terminator(R"((!))"), 
  Token::Terminator(R"((~))"), 
  Token::Terminator(R"((-))"), 
  Token::Terminator(R"((\+))"), 
  Token::Terminator(R"((\*))"), 
  Token::Terminator(R"((/))"), 
  Token::Terminator(R"((%))"), 
  Token::Terminator(R"((<))"), 
  Token::Terminator(R"((>))"), 
  Token::Terminator(R"((\^))"), 
  Token::Terminator(R"((\|))"), 
  Token::Terminator(R"((?))"), 
  Token::Terminator(R"([ \t\v\n\r\f])"), 
  Token::Terminator(R"(.)"), 
};
vector<DfaModel> lexical_tokens_dfa = {
  RegEx(R"((/\*))").GetDfaModel(), 
  RegEx(R"((//)[^\n\r]*)").GetDfaModel(), 
  RegEx(R"((auto))").GetDfaModel(), 
  RegEx(R"((_Bool))").GetDfaModel(), 
  RegEx(R"((break))").GetDfaModel(), 
  RegEx(R"((case))").GetDfaModel(), 
  RegEx(R"((char))").GetDfaModel(), 
  RegEx(R"((_Complex))").GetDfaModel(), 
  RegEx(R"((const))").GetDfaModel(), 
  RegEx(R"((continue))").GetDfaModel(), 
  RegEx(R"((default))").GetDfaModel(), 
  RegEx(R"((do))").GetDfaModel(), 
  RegEx(R"((double))").GetDfaModel(), 
  RegEx(R"((else))").GetDfaModel(), 
  RegEx(R"((enum))").GetDfaModel(), 
  RegEx(R"((extern))").GetDfaModel(), 
  RegEx(R"((float))").GetDfaModel(), 
  RegEx(R"((for))").GetDfaModel(), 
  RegEx(R"((goto))").GetDfaModel(), 
  RegEx(R"((if))").GetDfaModel(), 
  RegEx(R"((_Imaginary))").GetDfaModel(), 
  RegEx(R"((inline))").GetDfaModel(), 
  RegEx(R"((int))").GetDfaModel(), 
  RegEx(R"((long))").GetDfaModel(), 
  RegEx(R"((register))").GetDfaModel(), 
  RegEx(R"((restrict))").GetDfaModel(), 
  RegEx(R"((return))").GetDfaModel(), 
  RegEx(R"((short))").GetDfaModel(), 
  RegEx(R"((signed))").GetDfaModel(), 
  RegEx(R"((sizeof))").GetDfaModel(), 
  RegEx(R"((static))").GetDfaModel(), 
  RegEx(R"((struct))").GetDfaModel(), 
  RegEx(R"((switch))").GetDfaModel(), 
  RegEx(R"((typedef))").GetDfaModel(), 
  RegEx(R"((union))").GetDfaModel(), 
  RegEx(R"((unsigned))").GetDfaModel(), 
  RegEx(R"((void))").GetDfaModel(), 
  RegEx(R"((volatile))").GetDfaModel(), 
  RegEx(R"((while))").GetDfaModel(), 
  RegEx(R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)").GetDfaModel(), 
  RegEx(R"(0[xX][a-fA-F0-9]+((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)").GetDfaModel(), 
  RegEx(R"(0[0-7]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)").GetDfaModel(), 
  RegEx(R"([1-9][0-9]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)").GetDfaModel(), 
  RegEx(R"(L?'(\\.|[^\\'\n\r])+')").GetDfaModel(), 
  RegEx(R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)").GetDfaModel(), 
  RegEx(R"([0-9]*(\.)[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?)").GetDfaModel(), 
  RegEx(R"([0-9]+(\.)[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?)").GetDfaModel(), 
  RegEx(R"(0[xX][a-fA-F0-9]+([Pp][+-]?[0-9]+)(f|F|l|L)?)").GetDfaModel(), 
  RegEx(R"(0[xX][a-fA-F0-9]*(\.)[a-fA-F0-9]+([Pp][+-]?[0-9]+)?(f|F|l|L)?)").GetDfaModel(), 
  RegEx(R"(0[xX][a-fA-F0-9]+(\.)[a-fA-F0-9]*([Pp][+-]?[0-9]+)?(f|F|l|L)?)").GetDfaModel(), 
  RegEx(R"(L?"(\\.|[^\\"\n\r])*")").GetDfaModel(), 
  RegEx(R"((\.\.\.))").GetDfaModel(), 
  RegEx(R"((>>=))").GetDfaModel(), 
  RegEx(R"((<<=))").GetDfaModel(), 
  RegEx(R"((\+=))").GetDfaModel(), 
  RegEx(R"((-=))").GetDfaModel(), 
  RegEx(R"((\*=))").GetDfaModel(), 
  RegEx(R"((/=))").GetDfaModel(), 
  RegEx(R"((%=))").GetDfaModel(), 
  RegEx(R"((&=))").GetDfaModel(), 
  RegEx(R"((\^=))").GetDfaModel(), 
  RegEx(R"((\|=))").GetDfaModel(), 
  RegEx(R"((>>))").GetDfaModel(), 
  RegEx(R"((<<))").GetDfaModel(), 
  RegEx(R"((\+\+))").GetDfaModel(), 
  RegEx(R"((--))").GetDfaModel(), 
  RegEx(R"((->))").GetDfaModel(), 
  RegEx(R"((&&))").GetDfaModel(), 
  RegEx(R"((\|\|))").GetDfaModel(), 
  RegEx(R"((<=))").GetDfaModel(), 
  RegEx(R"((>=))").GetDfaModel(), 
  RegEx(R"((==))").GetDfaModel(), 
  RegEx(R"((!=))").GetDfaModel(), 
  RegEx(R"((;))").GetDfaModel(), 
  RegEx(R"((({)|(<%)))").GetDfaModel(), 
  RegEx(R"(((})|(%>)))").GetDfaModel(), 
  RegEx(R"((,))").GetDfaModel(), 
  RegEx(R"((:))").GetDfaModel(), 
  RegEx(R"((=))").GetDfaModel(), 
  RegEx(R"((\())").GetDfaModel(), 
  RegEx(R"((\)))").GetDfaModel(), 
  RegEx(R"(((\[)|(<:)))").GetDfaModel(), 
  RegEx(R"(((\])|(:>)))").GetDfaModel(), 
  RegEx(R"((\.))").GetDfaModel(), 
  RegEx(R"((&))").GetDfaModel(), 
  RegEx(R"((!))").GetDfaModel(), 
  RegEx(R"((~))").GetDfaModel(), 
  RegEx(R"((-))").GetDfaModel(), 
  RegEx(R"((\+))").GetDfaModel(), 
  RegEx(R"((\*))").GetDfaModel(), 
  RegEx(R"((/))").GetDfaModel(), 
  RegEx(R"((%))").GetDfaModel(), 
  RegEx(R"((<))").GetDfaModel(), 
  RegEx(R"((>))").GetDfaModel(), 
  RegEx(R"((\^))").GetDfaModel(), 
  RegEx(R"((\|))").GetDfaModel(), 
  RegEx(R"((?))").GetDfaModel(), 
  RegEx(R"([ \t\v\n\r\f])").GetDfaModel(), 
  RegEx(R"(.)").GetDfaModel(), 
};

/* section 5 */
stringstream input_stream;
Stream2TokenPipe s2ppl;
string yytext;

char input() {
  return s2ppl.input(input_stream);
}

void unput(char c) {
  s2ppl.unput(input_stream, c);
}

/* user code from lex file start */
int yywrap(void)
{
	return 1;
}


void comment(void)
{
	char c, prev = 0;
  
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	error("unterminated comment");
}


int column = 0;

void count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n' || yytext[i] == '\r')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}


int check_type(void)
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return TYPE_NAME;
*
*	return IDENTIFIER;
*/

/*
*	it actually will only return IDENTIFIER
*/

	return IDENTIFIER;
}


/* user code from lex file end */

/* section 6 */
//@variable
IdType to_syntax_token_id(Token lexical_token, AttrDict &ad) {
  string token_name = lexical_token.GetTokName();
  if (token_name == R"((/\*))") { 
    { { comment(); }}
  } else if (token_name == R"((//)[^\n\r]*)") { 
    { { /* consume //-comment */ }}
  } else if (token_name == R"((auto))") { 
    { { count(); return(AUTO); }}
  } else if (token_name == R"((_Bool))") { 
    { { count(); return(BOOL); }}
  } else if (token_name == R"((break))") { 
    { { count(); return(BREAK); }}
  } else if (token_name == R"((case))") { 
    { { count(); return(CASE); }}
  } else if (token_name == R"((char))") { 
    { { count(); return(CHAR); }}
  } else if (token_name == R"((_Complex))") { 
    { { count(); return(COMPLEX); }}
  } else if (token_name == R"((const))") { 
    { { count(); return(CONST); }}
  } else if (token_name == R"((continue))") { 
    { { count(); return(CONTINUE); }}
  } else if (token_name == R"((default))") { 
    { { count(); return(DEFAULT); }}
  } else if (token_name == R"((do))") { 
    { { count(); return(DO); }}
  } else if (token_name == R"((double))") { 
    { { count(); return(DOUBLE); }}
  } else if (token_name == R"((else))") { 
    { { count(); return(ELSE); }}
  } else if (token_name == R"((enum))") { 
    { { count(); return(ENUM); }}
  } else if (token_name == R"((extern))") { 
    { { count(); return(EXTERN); }}
  } else if (token_name == R"((float))") { 
    { { count(); return(FLOAT); }}
  } else if (token_name == R"((for))") { 
    { { count(); return(FOR); }}
  } else if (token_name == R"((goto))") { 
    { { count(); return(GOTO); }}
  } else if (token_name == R"((if))") { 
    { { count(); return(IF); }}
  } else if (token_name == R"((_Imaginary))") { 
    { { count(); return(IMAGINARY); }}
  } else if (token_name == R"((inline))") { 
    { { count(); return(INLINE); }}
  } else if (token_name == R"((int))") { 
    { { count(); return(INT); }}
  } else if (token_name == R"((long))") { 
    { { count(); return(LONG); }}
  } else if (token_name == R"((register))") { 
    { { count(); return(REGISTER); }}
  } else if (token_name == R"((restrict))") { 
    { { count(); return(RESTRICT); }}
  } else if (token_name == R"((return))") { 
    { { count(); return(RETURN); }}
  } else if (token_name == R"((short))") { 
    { { count(); return(SHORT); }}
  } else if (token_name == R"((signed))") { 
    { { count(); return(SIGNED); }}
  } else if (token_name == R"((sizeof))") { 
    { { count(); return(SIZEOF); }}
  } else if (token_name == R"((static))") { 
    { { count(); return(STATIC); }}
  } else if (token_name == R"((struct))") { 
    { { count(); return(STRUCT); }}
  } else if (token_name == R"((switch))") { 
    { { count(); return(SWITCH); }}
  } else if (token_name == R"((typedef))") { 
    { { count(); return(TYPEDEF); }}
  } else if (token_name == R"((union))") { 
    { { count(); return(UNION); }}
  } else if (token_name == R"((unsigned))") { 
    { { count(); return(UNSIGNED); }}
  } else if (token_name == R"((void))") { 
    { { count(); return(VOID); }}
  } else if (token_name == R"((volatile))") { 
    { { count(); return(VOLATILE); }}
  } else if (token_name == R"((while))") { 
    { { count(); return(WHILE); }}
  } else if (token_name == R"([a-zA-Z_]([a-zA-Z_]|[0-9])*)") { 
    { { count(); return(check_type()); }}
  } else if (token_name == R"(0[xX][a-fA-F0-9]+((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(0[0-7]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"([1-9][0-9]*((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(L?'(\\.|[^\\'\n\r])+')") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"([0-9]+([Ee][+-]?[0-9]+)(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"([0-9]*(\.)[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"([0-9]+(\.)[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(0[xX][a-fA-F0-9]+([Pp][+-]?[0-9]+)(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(0[xX][a-fA-F0-9]*(\.)[a-fA-F0-9]+([Pp][+-]?[0-9]+)?(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(0[xX][a-fA-F0-9]+(\.)[a-fA-F0-9]*([Pp][+-]?[0-9]+)?(f|F|l|L)?)") { 
    { { count(); return(CONSTANT); }}
  } else if (token_name == R"(L?"(\\.|[^\\"\n\r])*")") { 
    { { count(); return(STRING_LITERAL); }}
  } else if (token_name == R"((\.\.\.))") { 
    { { count(); return(ELLIPSIS); }}
  } else if (token_name == R"((>>=))") { 
    { { count(); return(RIGHT_ASSIGN); }}
  } else if (token_name == R"((<<=))") { 
    { { count(); return(LEFT_ASSIGN); }}
  } else if (token_name == R"((\+=))") { 
    { { count(); return(ADD_ASSIGN); }}
  } else if (token_name == R"((-=))") { 
    { { count(); return(SUB_ASSIGN); }}
  } else if (token_name == R"((\*=))") { 
    { { count(); return(MUL_ASSIGN); }}
  } else if (token_name == R"((/=))") { 
    { { count(); return(DIV_ASSIGN); }}
  } else if (token_name == R"((%=))") { 
    { { count(); return(MOD_ASSIGN); }}
  } else if (token_name == R"((&=))") { 
    { { count(); return(AND_ASSIGN); }}
  } else if (token_name == R"((\^=))") { 
    { { count(); return(XOR_ASSIGN); }}
  } else if (token_name == R"((\|=))") { 
    { { count(); return(OR_ASSIGN); }}
  } else if (token_name == R"((>>))") { 
    { { count(); return(RIGHT_OP); }}
  } else if (token_name == R"((<<))") { 
    { { count(); return(LEFT_OP); }}
  } else if (token_name == R"((\+\+))") { 
    { { count(); return(INC_OP); }}
  } else if (token_name == R"((--))") { 
    { { count(); return(DEC_OP); }}
  } else if (token_name == R"((->))") { 
    { { count(); return(PTR_OP); }}
  } else if (token_name == R"((&&))") { 
    { { count(); return(AND_OP); }}
  } else if (token_name == R"((\|\|))") { 
    { { count(); return(OR_OP); }}
  } else if (token_name == R"((<=))") { 
    { { count(); return(LE_OP); }}
  } else if (token_name == R"((>=))") { 
    { { count(); return(GE_OP); }}
  } else if (token_name == R"((==))") { 
    { { count(); return(EQ_OP); }}
  } else if (token_name == R"((!=))") { 
    { { count(); return(NE_OP); }}
  } else if (token_name == R"((;))") { 
    { { count(); return(';'); }}
  } else if (token_name == R"((({)|(<%)))") { 
    { { count(); return('{'); }}
  } else if (token_name == R"(((})|(%>)))") { 
    { { count(); return('}'); }}
  } else if (token_name == R"((,))") { 
    { { count(); return(','); }}
  } else if (token_name == R"((:))") { 
    { { count(); return(':'); }}
  } else if (token_name == R"((=))") { 
    { { count(); return('='); }}
  } else if (token_name == R"((\())") { 
    { { count(); return('('); }}
  } else if (token_name == R"((\)))") { 
    { { count(); return(')'); }}
  } else if (token_name == R"(((\[)|(<:)))") { 
    { { count(); return('['); }}
  } else if (token_name == R"(((\])|(:>)))") { 
    { { count(); return(']'); }}
  } else if (token_name == R"((\.))") { 
    { { count(); return('.'); }}
  } else if (token_name == R"((&))") { 
    { { count(); return('&'); }}
  } else if (token_name == R"((!))") { 
    { { count(); return('!'); }}
  } else if (token_name == R"((~))") { 
    { { count(); return('~'); }}
  } else if (token_name == R"((-))") { 
    { { count(); return('-'); }}
  } else if (token_name == R"((\+))") { 
    { { count(); return('+'); }}
  } else if (token_name == R"((\*))") { 
    { { count(); return('*'); }}
  } else if (token_name == R"((/))") { 
    { { count(); return('/'); }}
  } else if (token_name == R"((%))") { 
    { { count(); return('%'); }}
  } else if (token_name == R"((<))") { 
    { { count(); return('<'); }}
  } else if (token_name == R"((>))") { 
    { { count(); return('>'); }}
  } else if (token_name == R"((\^))") { 
    { { count(); return('^'); }}
  } else if (token_name == R"((\|))") { 
    { { count(); return('|'); }}
  } else if (token_name == R"((?))") { 
    { { count(); return('?'); }}
  } else if (token_name == R"([ \t\v\n\r\f])") { 
    { { count(); }}
  } else if (token_name == R"(.)") { 
    { { /* Add code to complain about unmatched characters */ }}
  } else  {
    return 0;
  }
  return 0;
}

#include "out_precompile.cpp" // generate parsing table
/* section 7 */
int main() {
  /* section 7.1 */
  spdlog::set_level(spdlog::level::err);
  

  /* section 7.3 */
  // lexical
  auto [transition, state] = sly::core::lexical::DfaModel::Merge(lexical_tokens_dfa);
  s2ppl = Stream2TokenPipe(transition, state, lexical_tokens, ending);
  // syntax
  sly::core::grammar::ParsingTable table;

  _defer_table(productions, start_syntax_token, ending, table);
  table.SetEndingToken(ending); // sb YZR
  LrParser parser(table);
  

  /* section 7.4 */
  // runtime
  {
    ifstream inputFile("../demo/1.in");
    input_stream << inputFile.rdbuf();
    inputFile.close();
  }

  // lexical
   vector<AttrDict> attributes;
   vector<Token> tokens;
   while (true) {
     auto lexical_token = s2ppl.Defer(input_stream);

     AttrDict ad;
     ad.Set("lval", s2ppl.buffer_); 
     ad.Set("row", s2ppl.token_begin_row_);
     ad.Set("col", s2ppl.token_begin_col_);
     yytext = s2ppl.buffer_;

     Token syntax_token;
     if (lexical_token == ending) {
       syntax_token = ending;
     } else {
       IdType id = to_syntax_token_id(lexical_token, ad);
       if (id == 0) 
         continue;
       syntax_token = syntax_tokens[id];
     }

     tokens.emplace_back(syntax_token);
     attributes.emplace_back(ad);

     // cerr << syntax_token.ToString() << " ";

     parser.ParseStep(tokens, attributes);
     if (lexical_token == ending) {
       break;
     }
   }
   cerr << endl;

  // syntax
  auto tree = parser.GetTree();
  cerr << "parse tree: " << endl;
  tree.PrintForShort(std::cerr, false);

  return 0;
}

