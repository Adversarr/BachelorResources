#lang racket

(require "types.rkt")
(require "syntax-define.rkt")
(require "build.rkt")
(require "../lex/lexer.rkt")

; Lexical Analysis
(define file-to-analysis
  (command-line
   #:program "Lexical Analyser"
   #:args ([filename "test1.pas"])
   filename))

(define content
  (bytes->string/utf-8 (file->bytes file-to-analysis)))

(displayln content)

(define gen (lexical-generator content))


; Non-terminate symbols
(define STX-FAKE-S
  (syntax-item "<augmented>" 0 (void)))

(define STX-EXPR
  (syntax-item "<expr>" 0 (void)))

(define STX-EOF (syntax-item "EOF" 1024 (lambda (tok) (void? tok))))

(define STX-PARTS
  (syntax-item "<parts>" 0 (void)))

(define STX-PART
  (syntax-item "<part>" 0 (void)))

(define STX-PROGRAM
  (syntax-item "<program>" 0 (void)))

(define STX-BLOCK
  (syntax-item "<block>" 0 (void)))

(define STX-STMT-LIST
  (syntax-item "<stmt-list>" 0 (void)))

(define STX-STMT
  (syntax-item "<stmt>" 0 (void)))

(define STX-BRANCH
  (syntax-item "<branch>" 0 (void)))

(define STX-WHILE-LOOP
  (syntax-item "<while-loop>" 0 (void)))

(define STX-DEFINITION
  (syntax-item "<definition-block>" 0 (void)))

(define STX-PARAM-LIST
  (syntax-item "<parameter-list>" 0 (void)))

(define STX-PARAM-LIST-INSIDE
  (syntax-item "<parameter-list-inside>" 0 (void)))
(define STX-PARAM
  (syntax-item "<param>" 0 (void)))

(define STX-VAR-LIST
  (syntax-item "<variable-list>" 0 (void)))

(define STX-VAR-LIST-INSIDE
  (syntax-item "<variable-list-inside>" 0 (void)))

(define STX-VAR-ITEM
  (syntax-item "<variable>" 0 (void)))

(define STX-VAR-NAME-LIST
  (syntax-item "<var-identifier-list>" 0 (void)))

(define STX-FCALL
  (syntax-item "<func-call>" 0 (void)))

(define STX-TYPE
  (syntax-item "<type>" 0 (void)))

(define STX-FCALL-PARAM
  (syntax-item "<func-param>" 0 (void)))


(define productions
  (list
   (production STX-FAKE-S (list STX-PARTS))
   (production STX-PARTS (list STX-PART))
   (production STX-PARTS (list STX-PART STX-PARTS))
   (production STX-PART (list STX-DEFINITION STX-BLOCK))
   (production STX-TYPE (list stx-identifier))
   (production STX-TYPE (list
                         STX-TYPE
                         stx-sep-square-lbracket
                         stx-number
                         stx-sep-square-rbracket))

   ; definition block can be function / program / procedure

   ; Functions:
   (production STX-DEFINITION (list stx-keyword-function
                                    stx-identifier
                                    STX-PARAM-LIST
                                    stx-sep-colon
                                    STX-TYPE
                                    STX-VAR-LIST))
   (production STX-DEFINITION (list stx-keyword-function
                                    stx-identifier
                                    STX-PARAM-LIST
                                    stx-sep-colon
                                    stx-identifier))


   ; main program
   (production STX-DEFINITION (list stx-keyword-program
                                    stx-identifier
                                    stx-sep-semicolon
                                    STX-VAR-LIST))

   ; Parameter list:
   (production STX-PARAM-LIST (list stx-sep-lbracket stx-sep-rbracket))
   (production STX-PARAM-LIST (list stx-sep-lbracket STX-PARAM-LIST-INSIDE stx-sep-rbracket))
   (production STX-PARAM-LIST-INSIDE (list STX-PARAM stx-sep-comma STX-PARAM-LIST-INSIDE))
   (production STX-PARAM-LIST-INSIDE (list STX-PARAM))
   (production STX-PARAM (list stx-identifier stx-sep-colon STX-TYPE))

   ; Variable list:
   (production STX-VAR-LIST (list stx-keyword-var STX-VAR-LIST-INSIDE))
   (production STX-VAR-LIST-INSIDE (list STX-VAR-ITEM STX-VAR-LIST-INSIDE))
   (production STX-VAR-LIST-INSIDE (list STX-VAR-ITEM))
   (production STX-VAR-ITEM (list STX-VAR-NAME-LIST stx-sep-colon STX-TYPE stx-sep-semicolon))
   (production STX-VAR-NAME-LIST (list stx-identifier))
   (production STX-VAR-NAME-LIST (list stx-identifier STX-VAR-NAME-LIST))

   ; Definition for a block of program. (or just one statement)
   (production STX-BLOCK (list stx-keyword-begin STX-STMT-LIST stx-keyword-end))
   (production STX-BLOCK (list stx-keyword-begin stx-keyword-end))
   (production STX-BLOCK (list STX-STMT))
   ; Definition for statements.
   (production STX-STMT (list STX-EXPR stx-sep-semicolon))
   (production STX-STMT-LIST (list STX-STMT))
   (production STX-STMT-LIST (list STX-STMT STX-STMT-LIST))

   ; Definition for if ... then ... else ...
   (production STX-STMT (list STX-BRANCH))
   (production STX-BRANCH(list stx-keyword-if STX-BLOCK))
   (production STX-BRANCH(list stx-keyword-if STX-BLOCK stx-keyword-else STX-BLOCK))

   ; Definition for while loop
   (production STX-STMT (list STX-WHILE-LOOP))
   (production STX-WHILE-LOOP (list stx-keyword-while stx-sep-lbracket STX-EXPR
                                    stx-sep-rbracket STX-BLOCK))

   ; Definition for expressions
   (production STX-EXPR (list stx-sep-lbracket STX-EXPR stx-sep-rbracket))
   (production STX-EXPR (list STX-EXPR stx-relop-plus STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-minus STX-EXPR))
   (production STX-EXPR (list STX-FCALL))
   (production STX-EXPR (list STX-EXPR stx-relop-divide STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-assign STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-multi STX-EXPR))
   (production STX-EXPR (list stx-number))
   (production STX-EXPR (list stx-identifier))
   (production STX-FCALL (list stx-identifier stx-sep-lbracket STX-FCALL-PARAM stx-sep-rbracket))
   (production STX-FCALL (list stx-identifier stx-sep-lbracket stx-sep-rbracket))
   (production STX-FCALL-PARAM (list STX-EXPR stx-sep-comma STX-FCALL-PARAM))
   (production STX-FCALL-PARAM (list STX-EXPR))
   ))

(define aug
  (LRItem STX-FAKE-S (list) (list STX-PARTS) STX-EOF))

(time
 (let ([automata (build-lr1-automata productions aug STX-EOF)])
   (let ([retval (automata gen)])
     (printf "Content of ~a is:\n~a\n################## RESULT OF LR[1] ##################\n\n" file-to-analysis content)
     (display-tree-mma retval))))

(printf "\n\n################## RESULT OF LR[1] ##################\n")