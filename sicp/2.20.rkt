#!/usr/bin/env racket
#lang racket

(define (prepend l1 l2)
  (cons (car l1) l2))

(define (reverse-iter l1 l2)
  (if (null? (cdr l1))
    (prepend l1 l2)
    (reverse-iter (cdr l1) (prepend l1 l2))))

(define (reverse l)
  (reverse-iter l '()))

(define (iseven n) (= (remainder n 2) 0))

(define (only-parity input stack isparity)
  (if (null? input)
    (reverse stack)
    (if (isparity (car input))
      (only-parity (cdr input) (cons (car input) stack) isparity)
      (only-parity (cdr input) stack isparity))))

(define (same-parity . input)
  (if (iseven (car input))
    (only-parity input '() iseven)
    (only-parity input '() (lambda (n) (not (iseven n))))))

(same-parity  1 2 3 4 5 6 7)
(same-parity 2 3 4 5 6 7)
