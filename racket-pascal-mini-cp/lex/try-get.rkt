#lang racket

(provide try-relop)
(provide try-keyword)
(provide try-sep)

; keyword definitions
(define (try-keyword id)
  (cond
    [(string=? id "and") "and"]
    [(string=? id "begin") "begin"]
    [(string=? id "div") "div"]
    [(string=? id "do") "do"]
    [(string=? id "else") "else"]
    [(string=? id "end") "end"]
    [(string=? id "for") "for"]
    [(string=? id "function") "function"]
    [(string=? id "if") "if"]
    [(string=? id "in") "in"]
    [(string=? id "nil") "nil"]
    [(string=? id "not") "not"]
    [(string=? id "of") "of"]
    [(string=? id "procedure") "procedure"]
    [(string=? id "program") "program"]
    [(string=? id "repeat") "repeat"]
    [(string=? id "set") "set"]
    [(string=? id "then") "then"]
    [(string=? id "to") "to"]
    [(string=? id "until") "until"]
    [(string=? id "var") "var"]
    [(string=? id "while") "while"]
    [else #f]))

(define (try-sep ch)
  (cond
    [(char=? ch #\[) "square-lbracket"]
    [(char=? ch #\]) "square-rbracket"]
    [(char=? ch #\)) "rbracket"]
    [(char=? ch #\() "lbracket"]
    [(char=? ch #\;) "semicolon"]
    [(char=? ch #\,) "comma"]
    [else #f]))

(define (try-relop s)
  (cond
    [(string=? s ":") "colon"]
    [(string=? s "<=") "leq"]
    [(string=? s ">=") "geq"]
    [(string=? s "<") "lt"]
    [(string=? s ">") "gt"]
    [(string=? s "<>") "neq"]
    [(string=? s "=") "eq"]
    [(string=? s ":=") "assign"]
    [(string=? s "..") "double-dot"]
    [(string=? s ".") "dot"]
    [(string=? s "+") "plus"]
    [(string=? s "-") "minus"]
    [(string=? s "*") "multi"]
    [(string=? s "/") "divide"]
    [else #f]))