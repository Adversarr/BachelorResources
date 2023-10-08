#lang racket

(require "types.rkt")
(require "syntax-define.rkt")
(require "build.rkt")
(require "../lex/lexer.rkt")
(require racket/generator)


(define STX-FAKE-S
  (syntax-item "<augmented>" 0 (void)))
(define STX-S
  (syntax-item "<S>" 0 (void)))

(define STX-C
  (syntax-item "<C>" 0 (void)))

(define STX-c
  (syntax-item "<c>" 0 (lambda (ch) (char=? #\c ch))))

(define STX-d
  (syntax-item "<d>" 0 (lambda (ch) (char=? #\d ch))))

(define STX-EOF (syntax-item "EOF" 1024 (lambda (tok) (void? tok))))

(define productions
  (list
   (production STX-FAKE-S (list STX-S))
   (production STX-S (list STX-C STX-C))
   (production STX-C (list STX-c STX-C))
   (production STX-C (list STX-d))))

(define aug
  (LRItem STX-FAKE-S (list) (list STX-S) STX-EOF))

(define gen
  (let ([s (string->list "cdccd")])
    (generator ()
               (let rec ([l s])
                 (if (empty? l)
                     (void)
                     (begin
                       (yield (first l))
                       (rec (rest l))))))))

(time
 (let ([automata (build-lr1-automata productions aug STX-EOF)])
   (let ([retval (automata gen)])
     (display-tree-mma retval))))

(printf "\n\n################## RESULT OF LR[1] ##################\n")
