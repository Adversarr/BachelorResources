#lang racket

(require "types.rkt")
(require "syntax-define.rkt")
(require "closure.rkt")

(define go
  (lambda (item-list a)
    (flatten
     (for/list ([item item-list])
       (if (empty? (LRItem-right-tail item))
           (list)
           (if (eq? a (first (LRItem-right-tail item)))
               (LRItem
                (LRItem-left item)
                (append (LRItem-right-head item) (list (first (LRItem-right-tail item))))
                (rest (LRItem-right-tail item))
                (LRItem-look-ahead item))
               (list)))))))



(define (closure-eq2? a b)
  (all-true?
   (for/list ([ia a])
     (any-true?
      (for/list ([ib b])
        (LRItem-equal? ia ib)))
     )))

(define (closure-eq? a b)
  (if (empty? a)
      (if (empty? b)
          #t    ; a 和 b 都为空
          #f)   ; a 空 b 不空
      (let rec ([ca a])
        (cond
          [(empty? ca) #t]
          [else
           (if (any-true?
                (for/list ([ib b])
                  (LRItem-equal? (first ca) ib)))
               (rec (rest ca))
               #f)]))))


(provide (all-defined-out))
