#lang racket

(provide lteq?)
(provide gteq?)
(provide lt?)
(provide gt?)
(provide in-range?)
(provide digit?)
(provide letter?)
(provide relop-letter?)
(provide letter_?)
(provide ws?)

(define (ws? ch)
  (or
   (char=? ch #\space)
   (char=? ch #\tab)
   (char=? ch #\newline)
   (char=? ch #\return)))


; Here Define some critical functions to support the recognition
(define (lteq? a b)
  (<= (char->integer a) (char->integer b)))

(define (gteq? a b)
  (>= (char->integer a) (char->integer b)))

(define (lt? a b)
  (not (gteq? a b)))

(define (gt? a b)
  (not (lteq? a b)))

(define (in-range? a l r)
  (and (lteq? l a)
       (lteq? a r)))


(define (digit? ch)
  (in-range? ch #\0 #\9))

(define (letter? ch)
  (or (in-range? ch #\A #\Z)) (in-range? ch #\a #\z))

(define (letter_? ch)
  (or (letter? ch) (eq? ch #\_)))

(define (relop-letter? ch)
  (cond
    [(char=? ch #\<) #t]
    [(char=? ch #\=) #t]
    [(char=? ch #\>) #t]
    [(char=? ch #\:) #t]
    [(char=? ch #\.) #t]
    [(char=? ch #\+) #t]
    [(char=? ch #\-) #t]
    [(char=? ch #\*) #t]
    [(char=? ch #\/) #t]
    [else #f]))