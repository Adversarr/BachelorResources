#lang racket

(require "types.rkt")
(require "closure.rkt")
(require "goto.rkt")
(require data/queue)

(define (look-ahead-and-reduce lritem-list sym)
  (for/list ([lri lritem-list]
             #:when(and (empty? (LRItem-right-tail lri))
                        (eq? sym (LRItem-look-ahead lri))))
    lri))

(define (try-to-shift-in lritem-list sym)
  (for/list ([lri lritem-list]
             #:when(and (not (empty? (LRItem-right-tail lri)))
                        (eq? sym (first (LRItem-right-tail lri)))))
    lri))

(define (get-all-terminals prod)
  (set->list(list->set(filter terminal? (flatten (for/list ([p prod]) (production-right p)))))))

(define (stx-can-go item-list)
  (set->list
   (list->set
    (for/list
        ([i item-list]
         #:when (not (empty? (LRItem-right-tail i))))
      (first (LRItem-right-tail i))))))

(define (costom-list-member? eqf lst item)
  (if (empty? lst)
      #f
      (if (eqf item (first lst))
          #t
          (costom-list-member? eqf (rest lst) item))))

(define (build-lr1-automata prod-list augmented-item eof-syntax)
  (define closure (get-closure-function prod-list))

  (define I0 (closure (list augmented-item)))
  
  (define term->stx-item
    (let ([all-terminals (get-all-terminals prod-list)])
      (for-each (lambda (t) (printf "Found:\t~a\n" t)) all-terminals)
      (lambda (tok)
        (if ((syntax-item-matcher eof-syntax) tok)
            eof-syntax
            (let ([stxl (for/list
                         ([t all-terminals]
                          #:when((syntax-item-matcher t) tok))
                         t)])
              (if (empty? stxl)
                  (printf "ERROR: cannot identify this terminal.~a\n" tok)
                  (first stxl)))))))

  (define (generate-closure-from item-list)
    (for/list ([stx (stx-can-go item-list)])
      (closure (go item-list stx))))

  (define (find-not-in clist c)
    (for/list ([clos (generate-closure-from c)]
               #:when(not(costom-list-member? closure-eq? clist clos)))
      clos))

  (define all-closures (let ([q (make-queue)])
                         (enqueue! q I0)
                         (let expand-closure ([result (list)])
                           (if (queue-empty? q)
                               result
                               (let* ([top (dequeue! q)])
                                 (printf "ITERATING NEXT...\n")
                                 (for-each (lambda (i)
                                             (printf "\t")
                                             (display-lritem i)) top)
                                 (set! result (append result (list top)))
                                 (for-each
                                  (lambda (g) (enqueue! q g))
                                  (find-not-in result top))
                                 (expand-closure result))))))

  (define goto
    (let ([ht (make-hash)])
      (for-each (lambda (c) (hash-set! ht c (make-hash))) all-closures)
      (for*/list ([c1 all-closures]
                  [c2 all-closures])
        (for/list ([stx (stx-can-go c1)]
                   #:when(closure-eq? (closure (go c1 stx)) c2))
          (hash-set! (hash-ref ht c1) stx c2)))
      (lambda (cl stx) (hash-ref (hash-ref ht cl) stx))))

  (define (work-on-generator gen)
    (let ([ht (make-hash)]
          [sym (gen)])
      (for-each
       (begin
         (lambda (c)
           (hash-set!
            ht c
            (lambda (sym)
              (let redo ([buffer sym])
                (printf "Entering state(closure):\n")
                (for-each (lambda (c) (display "\t- ") (display-lritem c)) c)
                (define buf (if (or (syntax-item? buffer)
                                    (pair? buffer)) buffer (term->stx-item buffer)))
                (printf "Received a symbol [[")
                (if (pair? buf)
                    (printf "~a" (syntax-item-id (syntax-tree-node-head (car buf))))
                    (printf "~a" (syntax-item-id buf)))
                (displayln "]]\n\tCurrent Closure is \n")
                (for-each (lambda (c) (display "\t- ") (display-lritem c)) c)
                (define (shift-in-helper retval matched-stx transformer)
                  (let ([prod-in-use (cdr (car (car retval)))]
                        [prod-head (car (car (car retval)))]
                        [stack (cdr (car retval))]
                        [next-symbol-in-buffer (cdr retval)])

                    (printf "Reducing... \n")
                    (for-each (lambda (c) (display "\t- ") (display-lritem c)) c)

                    (define stack-added (append
                                         stack
                                         (list (transformer
                                                matched-stx
                                                prod-in-use))))

                    (printf "\tcurrently in stack is\n\t[")
                    (for-each
                     (lambda (item)
                       (printf "\n\t\t- ")
                       (display-tree item))
                     (reverse stack-added))
                    (printf "\n\t]\n")

                    (if (eq? (length prod-in-use) 1)
                        ; reduce complete!
                        ; 当前的CLOSURE中一定有一个能够处理当前的syntax-node 对应的非终结符 （即执行了goto操作）
                        (let ([final-tree  (syntax-tree-node prod-head (reverse stack-added))])
                          (printf "Reduce done!!! now goto another state...(redo) Tree is\n\t")
                          (display-tree final-tree)
                          (printf "\n")
                          (printf "From state:\n")
                          (for-each (lambda (c) (display "\t- ") (display-lritem c)) c)
                          (printf "To..")
                          (redo (cons final-tree next-symbol-in-buffer)))
                        ; reduce 还没有结束，继续退栈
                        (begin
                          (printf "\tReduce not complete : prod left is ~a\n" prod-in-use)
                          (cons (cons (cons prod-head (rest prod-in-use))
                                      stack-added)
                                next-symbol-in-buffer)))))
                (if (pair? buf)
                    (let ([nt-tree-node (car buf)]
                          [next-symbol-in-buf (cdr buf)])
                      (printf "Here reduction complete when look-ahead is ~a\nAlso for the tree...\n\t" next-symbol-in-buf)
                      (begin (display-tree nt-tree-node) (displayln ""))
                      (printf "Current state is\n")
                      (for-each (lambda (c) (display "\t- ") (display-lritem c)) c)
                      (if (eq? (syntax-tree-node-head nt-tree-node)  (LRItem-left augmented-item))
                          (begin
                            (printf "All done!!!\n") ; Augmented item
                            (display-tree nt-tree-node)
                            (printf "\n\nExiting...\n\n")
                            nt-tree-node)
                          (let* ([next-state (hash-ref ht (goto c (syntax-tree-node-head nt-tree-node)))]
                                 [retval (next-state next-symbol-in-buf)])
                            (shift-in-helper retval nt-tree-node (lambda (m p) m)))))
                    (let ([item-can-reduce (look-ahead-and-reduce c buf)]
                          [item-can-shiftin (try-to-shift-in c buf)])
                      ; 接收到一个终结符号，执行移进或者规约
                      (printf "\tItem->Reduce:~a\n" (length item-can-reduce))
                      (printf "\tItem->Shift: ~a\n" (length item-can-shiftin))
                      (define (reduce)
                        (if (< 1 (length item-can-reduce)); reduce to a list and do nothing.
                            (displayln "Error: cannot decide which prod to reduce")
                            (let ([item (first item-can-reduce)])
                              ; return the production
                              (printf "Reduce! (look-ahead = ~a) use item: \n\t" buf)
                              (display-lritem item)
                              (cons
                               (cons
                                (cons
                                 (LRItem-left item)
                                 (reverse (LRItem-right-head item)))
                                (list))
                               buffer))))
                      (define (shift-in)
                        (let* ([matched-stx buf]
                               [next-state (hash-ref ht (goto c matched-stx))])
                          (printf "Shift in! \n\tMatched<~a>-stx is ~a \n" buffer matched-stx)
                          (let([retval (next-state (gen))])
                            (if (syntax-tree-node? retval)
                                (display-tree retval)
                                (void))
                            (shift-in-helper
                             retval
                             matched-stx
                             (lambda (matched-stx prod-in-use)
                               (syntax-tree-node
                                (first prod-in-use)
                                (matched-item matched-stx buffer)))))))
                      (if (empty? item-can-shiftin)
                          (if (empty? item-can-reduce)
                              (begin
                                (displayln "Error. nothing to do...")
                                (void)) ;error.
                              (reduce))
                          (if (empty? item-can-reduce)
                              ; shift in the terminal and go to another state.
                              ; 执行 移进 + 转下一状态
                              (shift-in)
                              (begin ; not clear -> decide on priority! or error here.
                                (displayln "Cannot decide which to use (RS).\n reduce is\n")
                                (for-each display-lritem item-can-reduce)
                                (printf "\nshift-in is\n")
                                (for-each display-lritem item-can-shiftin)
                                (if (eq? 1 (length item-can-reduce))
                                    (let ([head (LRItem-right-head (first item-can-reduce))])
                                      (if (>= (length head) 2)
                                          (if (syntax-item? (second (reverse head)))
                                              (begin
                                                (printf "But I found that I can decide by syntax ~a\n"
                                                        (second(reverse head)))
                                                (let ([prio-shift-in (syntax-item-priority (first (LRItem-right-tail (first item-can-shiftin))))]
                                                      [prio-reduce (syntax-item-priority (second(reverse head)))])
                                                  (if (> prio-shift-in prio-reduce)
                                                      (shift-in)
                                                      (reduce))))
                                              (void)) ; error
                                          (void)))    ; error
                                    (void)))))))))))) ; error
       all-closures)
      ((hash-ref ht I0) sym)))
  work-on-generator)

(provide build-lr1-automata)