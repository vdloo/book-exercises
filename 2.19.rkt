#!/usr/bin/env racket
#lang racket

(define first-denomination
  (λ (coin-values) (car coin-values)))

(define except-first-denomination 
  (λ (coin-values) (cdr coin-values)))

(define no-more?
  (λ (coin-values) 
     (null? coin-values)))

(define cc
  (λ (amount coin-values) 
     (cond ((= amount 0) 1)
	((or (< amount 0) (no-more? coin-values)) 0)
	(else
	  (+ (cc amount
		 (except-first-denomination coin-values))
	     (cc (- amount
		    (first-denomination coin-values))
		 coin-values))))))

(define us-coins (list 50 25 10 5 1))
(define uk-coins (list 100 50 20 10 5 2 1 0.5))

(printf "you can change 100 dollars ~a ways\n" (cc 100 us-coins))
(printf "you can change 100 uk pounds ~a ways\n"(cc 100 uk-coins))

(define (prepend l1 l2)
  (cons (car l1) l2))

(define (reverse-iter l1 l2)
  (if (null? (cdr l1))
    (prepend l1 l2)
    (reverse-iter (cdr l1) (prepend l1 l2))))

(define (reverse l)
  (reverse-iter l '()))

; it doesn't matter because all the permuations are recursively calculated
(printf "you can still change 100 dollars ~a ways after changing the order of the coins\n" (cc 100 (reverse us-coins)))
