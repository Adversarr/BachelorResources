#lang racket

(require "types.rkt")
(require "syntax-define.rkt")

; (define (in-lritem-list? st a)
;   (any-true?
;    (for/list ([lri st])
;      (LRItem-equal? lri a))))


(define (in-lritem-list? st a)
  (cond
    [(empty? st) #f]
    [(LRItem-equal? (first st) a) #t]
    [else (in-lritem-list? (rest st) a)]))

(define (list-member? st a eqf) (any-true? (for/list ([i st]) (eqf i st))))
(define (uniquify l eqf)
  (if (empty? l)
      l
      (let ([r (uniquify (rest l) eqf)])
        (if (list-member? r (first l) eqf)
            r
            (append r (list (first l)))))))

(define (get-look-ahead prod)
  (define non-terminals
    (set->list
     (list->set
      (filter
       non-terminal?
       (flatten (for/list ([p prod])
                  (list (production-right p) (list (production-left p)))))))))
  (displayln non-terminals)
  (define (update-firsts first-set)
    (let ([ht (make-hash)])
      (for/list ([nt-first first-set]
                 [nt non-terminals])
        (hash-set! ht nt nt-first))
      (for/list ([nt-first first-set]
                 [nt non-terminals])
        (list->set
         (flatten(for/list ([p prod])
                   (if (eq? nt (production-left p))
                       (if (terminal? (first (production-right p)))
                           (first (production-right p))
                           (set->list (hash-ref ht (first (production-right p)))))
                       (list))))))))
  (define (get-firsts first-set)
    (let ([updated (update-firsts first-set)])
      (if (any-true?
           (for/list ([a updated]
                      [b first-set])
             (begin
               (not (set=? a b)))))
          (get-firsts updated)
          updated)))
  (let ([first-set (get-firsts (for/list ([i non-terminals]) (set)))])
    (for/list ([nt non-terminals]
               [fi first-set])
      (begin
        (printf "First[ ~a ] = {" (syntax-item-id nt))
        (for/set ([i fi])
          (printf "~a, " (syntax-item-id i)))
        (printf "}\n")
        )))
  ; Remark: Here we just assume the first stx is definitely a terminal symbol
  (let ([ht (make-hash)])
    (for/list ([nt-first (get-firsts (for/list ([i non-terminals]) (set)))]
               [nt non-terminals])
      (hash-set! ht nt nt-first))
    (define (syntax-first stx)
      (set->list (hash-ref ht stx (set stx))))
    (lambda (lritem)
      (let ([right-hand (LRItem-right-tail lritem)])
        (cond
          [(empty? right-hand) (void)]
          [(eq? 1 (length right-hand)) (list (LRItem-look-ahead lritem))]
          [(< 1 (length right-hand)) (syntax-first (first (rest right-hand)))])))))




(define (get-closure-function prod-list)
  (define look-ahead (get-look-ahead prod-list))
  (define (infer item)
    (let ([right-hand (LRItem-right-tail item)])
      (if
       (empty? right-hand)
       (list)
       (flatten
        (for/list
            ([prod prod-list]
             #:when (eq? (production-left prod) (first right-hand)))
          (for/list ([la (look-ahead item)])
            (begin
              (LRItem
               (production-left prod)
               (list)
               (production-right prod)
               la))))))))
  (define (lr1-closure lritem-list)
    (let ([addon '()])
      ; infer from prod-list and lritem-set
      (for-each
       (lambda (item)
         (for-each
          (lambda (infered-item)
            (if (and (not (in-lritem-list? lritem-list infered-item))
                     (not (in-lritem-list? addon infered-item)))
                (begin
                  ; (display-lritem infered-item)
                  (set! addon (append addon (list infered-item))))
                (void)))
          (infer item)))
       lritem-list)
      (if (empty? addon)
          (begin
            ; (displayln "Closure Done!")
            lritem-list)
          (begin
            ; (printf "Addon is:\n")
            ; (for-each display-lritem addon)
            (lr1-closure (append lritem-list addon))))))
  lr1-closure)





(provide get-closure-function)
(provide in-lritem-list?)