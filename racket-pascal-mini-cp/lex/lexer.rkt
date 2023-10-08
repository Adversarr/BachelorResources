#lang racket

(require racket/generator)
(require "basic-utils.rkt")
(require "matchers.rkt")
(require "token.rkt")
(require "try-get.rkt")



(define (get-token str)
  (let* ([buffer (string->list str)]
         [s (first buffer)]) ; s: the first char in buffer
    (cond
      ; Matching whitespace
      [(ws? s)
       (let ([matched (Whitespace! buffer)])
         (token (list->string matched) token-whitespace (void)))]
      ; Matching seperator
      [(try-sep s)
       (token (list->string (list s)) token-sep (try-sep s))]
      ; Matching numbers
      [(digit? s)
       (let ([matched (Number! buffer)])
         (if (void? matched)
             ; Look Forward.
             (let ([matched (ArrayIndex! buffer)])
               (if (void? matched)
                   (void)
                   (if (and
                        (>= (string-length str) (+ 2 (length matched)))
                        (string=? ".." (substring str (length matched) (+ 2 (length matched)))))
                       (token (list->string matched) token-number (void))
                       (void))))
             (token (list->string matched) token-number (void))
             ))]
      [(relop-letter? s)
       (let ([matched (Relop! buffer)])
         (if (void? matched)
             (void)
             (let ([content (list->string matched)])
               (token content token-relop (try-relop content)))))]
      ; Matching identifier/keyword
      [(letter_? s)
       (let ([matched (Identifier! buffer)])
         (if (void? matched)
             (void)
             (let* ([content (list->string matched)]
                    [kw (try-keyword content)])
               (if kw
                   (token content token-keyword kw)
                   (token content token-identifier content))
               )))]
      [(char=? #\' s)
       (let ([matched (String! buffer)])
         (if (void? matched)
             (void)
             (let ([content (list->string matched)])
               (token content token-string content))))]
      [else (println "Error.")])))

(define (lex-analyse str)
  (if (= (string-length str) 0)
      `()
      (let ([curr-token (get-token str)])
        ; (displayln curr-token)
        (if (not (token? curr-token))
            (printf "Illegal at ~s.\n" str) ; error
            (let* ([token-length (string-length (token-content curr-token))]
                   [sub-str (substring str token-length)]
                   [recur (lex-analyse sub-str)])
              (if (void? recur)
                  (void)
                  (cons curr-token recur)))))))

(define (postprocess l)
  (for/list ([i l])
    (match (token-type i)
      [(== token-whitespace) (struct-copy token i [content "<whitespace>"])]
      [else i])))

(define (lexical-generator s)
  (generator
   ()
   (let rec ([result (for/list ([i (lex-analyse s)]
                                #:when(match (token-type i)
                                         [(== token-whitespace) #f]
                                         [else #t])) i)])
     (if (empty? result)
         (void)
         (begin
           (yield (first result))
           (rec (rest result)))))))


(provide (all-defined-out))