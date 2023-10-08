#lang racket

(require "lexer.rkt")

(define file-to-analysis
  (command-line
   #:program "Lexical Analyser"
   #:args (filename)
   filename))


(define content
  (bytes->string/utf-8 (file->bytes file-to-analysis)))

(printf "Content of ~a is:\n~a\n################## RESULT OF LEXER ##################\n\n" file-to-analysis content)

(let ([result (postprocess (lex-analyse content))])
  (if (void? result)
      (printf "Error occured.\n")
      (for/list ([i result])
        (displayln i)))
  (void))