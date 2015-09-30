#!/usr/bin/env racket
#lang racket

(for-each (lambda (x) (printf "~a\n" x))
	(list 1 2 3 4 5))

(define my-foreach 
  (lambda (proc items)
    (if (null? items)
      ((lambda (result next) (next)) 
        (proc (car items) 
	(lambda () (my-foreach proc (cdr items))))) '())))

(for-each (lambda (x) (printf "~a\n" x))
	(list 1 2 3 4 5))

