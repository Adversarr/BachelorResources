#lang racket

(require "types.rkt")
(require "syntax-define.rkt")
(require "build.rkt")
(require "../lex/lexer.rkt")



(define file-to-analysis
  (command-line
   #:program "Lexical Analyser"
   #:args ([filename "test1.pas"])
   filename))

(define content
  (bytes->string/utf-8 (file->bytes file-to-analysis)))

(displayln content)

(define gen (lexical-generator content))


(define STX-FAKE-S
  (syntax-item "S'" 0 (void)))

(define STX-EXPR
  (syntax-item "S" 0 (void)))

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
   (production STX-FAKE-S (list STX-EXPR))
   (production STX-EXPR (list stx-sep-lbracket STX-EXPR stx-sep-rbracket))
   (production STX-EXPR (list STX-EXPR stx-relop-plus STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-minus STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-divide STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-assign STX-EXPR))
   (production STX-EXPR (list STX-EXPR stx-relop-multi STX-EXPR))
   (production STX-EXPR (list stx-number))
   (production STX-EXPR (list stx-identifier))))

(define aug
  (LRItem
   STX-FAKE-S
   (list)
   (list STX-EXPR)
   STX-EOF))


(time
 (let ([automata (build-lr1-automata productions aug STX-EOF)])
   (let ([retval (automata gen)])
     (printf "Content of ~a is:\n~a\n################## RESULT OF LR[1] ##################\n\n" file-to-analysis content)
     (display-tree-mma retval))))
(printf "\n\n################## RESULT OF LR[1] ##################\n")