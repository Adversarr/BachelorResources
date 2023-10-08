#lang racket

(require "types.rkt")
(require "syntax-define.rkt")
(require "closure.rkt")
(require "goto.rkt")
(require "build.rkt")
(require "../lex/lexer.rkt")
(require racket/generator)

(define STX-FAKE-S
  (syntax-item "S'" 0 (void)))
(define STX-EXPR
  (syntax-item "S" 0 (void)))

(define STX-EOF (syntax-item "EOF" 1024 (lambda (tok) (void? tok))))


(define file-to-analysis
  (command-line
   #:program "Lexical Analyser"
   #:args ([filename "test1.pas"])
   filename))

(define content
  (bytes->string/utf-8 (file->bytes file-to-analysis)))

(displayln content)

(define gen (lexical-generator content))



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
   ; definition block can be function / program / procedure
   ; Functions:
   (production STX-DEFINITION (list stx-keyword-function
                                    stx-identifier
                                    STX-PARAM-LIST
                                    stx-sep-colon
                                    stx-identifier
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
   (production STX-BLOCK (list stx-keyword-begin stx-keyword-end))

   ))

(define aug
  (LRItem
   STX-FAKE-S
   (list)
   (list STX-PARTS)
   STX-EOF))

(let ([retval ((build-lr1-automata productions aug STX-EOF) gen)])
  (printf "Content of ~a is:\n~a\n################## RESULT OF LR[1] ##################\n\n" file-to-analysis content)
  (display-tree-mma retval))