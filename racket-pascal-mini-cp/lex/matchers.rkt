#lang racket

(require "basic-utils.rkt")
(provide Number!)
(provide Identifier!)
(provide Whitespace!)
(provide Relop!)
(provide ArrayIndex!)
(provide String!)

; DFA -- ArrayIndexSM
(define ArrayIndexSM
  (letrec ([s0 (lambda (ch) (cond
                              [(digit? ch) s1]
                              [else #f]))]
           [s1 (lambda (ch) (cond
                              [(digit? ch) s1]
                              [(letter_? ch) s1]
                              [else #t]))])
    s0))

; DFA -- number
(define NumberSM
  (letrec ([s0 (lambda (ch) (cond
                              [(digit? ch) s1]
                              [(letter_? ch) #f] ; -> error!
                              [else #f]))]
           [s1 (lambda (ch) (cond
                              [(digit? ch) s1]
                              [(char=? #\e ch) s3]
                              [(char=? #\. ch) s2]
                              [(letter_? ch) #f] ; -> error!
                              [else #t]))]
           [s2 (lambda (ch) (cond
                              [(digit? ch) s4]
                              [else #f]))]
           [s3 (lambda (ch) (cond
                              [(digit? ch) s5]
                              [(or (char=? ch #\+) (char=? ch #\-)) s6]
                              [else #f]))]
           [s4 (lambda (ch) (cond
                              [(digit? ch) s4]
                              [(char=? #\e ch) s3]
                              [(letter_? ch) #f]  ; -> error
                              [else #t]))]
           [s5 (lambda (ch) (cond
                              [(digit? ch) s5]
                              [(letter_? ch) #f]
                              [else #t]))]
           [s6 (lambda (ch) (cond
                              [(digit? ch) s5]
                              [else #f]))])
    s0))


; DFA -- identifier
(define IdentifierSM
  (letrec ([s0 (lambda (ch) (cond
                              [(letter_? ch) s1]
                              [else #f]))]
           [s1 (lambda (ch) (cond
                              [(letter_? ch) s1]
                              [(digit? ch) s1]
                              [else #t]))])
    s0))

; DFA -- ws
(define (WhitespaceSM ch)
  (if (ws? ch)
      WhitespaceSM
      #t))

; DFA -- relop
(define RelopSM
  (letrec ([s0 (lambda (ch) (cond
                              [(char=? ch #\+) s1]
                              [(char=? ch #\-) s1]
                              [(char=? ch #\*) s1]
                              [(char=? ch #\/) s1]
                              [(char=? ch #\=) s1]
                              [(char=? ch #\<) s2]
                              [(char=? ch #\>) s3]
                              [(char=? ch #\.) s4]
                              [(char=? ch #\:) s5]
                              [else #f]))]
           [s1 (lambda (ch) #t)]
           [s2 (lambda (ch) (cond
                              [(char=? ch #\=) s1]
                              [(char=? ch #\>) s1]
                              [else #t]))]
           [s3 (lambda (ch) (cond
                              [(char=? ch #\=)]
                              [else #t]))]
           [s4 (lambda (ch) (cond
                              [(char=? ch #\.) s1]
                              [else #t]))]
           [s5 (lambda (ch) (cond
                              [(char=? ch #\=) s1]
                              [else #t]))]

           )
    s0))

; DFA -- string
(define StringSM
  (let ([q? (lambda (ch) (char=? ch #\'))])
    (letrec ([s0 (lambda (ch)(cond
                               [(q? ch) s1]
                               [else #f]))]
             [s1 (lambda (ch) (cond
                                [(q? ch) s1]
                                [(char=? #\nul ch) #f]
                                [else s3]))]
             [s2 (lambda (ch) (cond
                                [(q? ch) s3]
                                [else #f]))]
             [s3 (lambda (ch) (cond
                                [(q? ch) s4]
                                [(char=? #\nul ch) #f]
                                [else s3]))]
             [s4 (lambda (ch) (cond
                                [(q? ch)s3]
                                [else #t]))])
      s0)))


; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;
; DFA is -- (K, Σ, f, S, Z)
; K -- state
; Σ -- char-set
; f -- changing map
; S -- start state
; Z -- final state set
;
; Therefore, a state can be described as a tuple that:
; 1. can-final?
; 2. transition
; describe by -- observe the result of *apply s to <char>*
; 1. #t -> final state and exit
; 2. #f -> not final state but exit
; 3. s  -> to next state.
; iter-until-fail -> list / void
; 1. list is empty     -> not accept
; 2. list is not empty -> accept

(define (iter-until-fail s l)
  (let* ([ch (if (empty? l)
                 #\null
                 (first l))] ; getch --> ch
         [t (s ch)])         ; transition {s --[ch]-> t}
    (if (boolean? t)         ; stop?
        (if t
            (list)           ; '() -> accept
            (void))          ; void -> fail
        (let ([result (iter-until-fail t (rest l))])
          (if (void? result)
              (void)         ; -> fail matching
              (cons ch result))
          ))))

(define (Identifier! buffer)
  (iter-until-fail IdentifierSM buffer))

(define (Number! buffer)
  (iter-until-fail NumberSM buffer))

(define (Whitespace! buffer)
  (iter-until-fail WhitespaceSM buffer))

(define (Relop! buffer)
  (iter-until-fail RelopSM buffer))
(define (ArrayIndex! buffer)
  (iter-until-fail ArrayIndexSM buffer))
(define (String! buffer)
  (iter-until-fail StringSM buffer))