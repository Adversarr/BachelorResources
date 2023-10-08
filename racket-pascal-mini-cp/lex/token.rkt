#lang racket


(require rebellion/type/enum)

(define-enum-type
  token-kind
  (token-identifier
   token-number
   token-string
   token-relop
   token-keyword
   token-sep
   token-whitespace))

(struct token
  (content type attribute)
  #:transparent)

(provide (all-defined-out))
