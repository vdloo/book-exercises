#lang sicp

(define (make-vect x y)
  (cons x y))

(define (xcor-vect vect)
  (car vect))

(define (ycor-vect vect)
  (cdr vect))

(define (vector-equals? vect-a vect-b)
  (and
   (= (xcor-vect vect-a) (xcor-vect vect-b))
   (= (ycor-vect vect-a) (ycor-vect vect-b))))

(define vect-start (make-vect 0 5))
(define vect-end (make-vect 5 0))

(define (make-segment vect-origin-to-start vect-origin-to-end)
  (cons vect-origin-to-start vect-origin-to-end))

(define (start-segment segment)
  (car segment))

(define (end-segment segment)
  (cdr segment))

(define segment (make-segment vect-start vect-end))

(vector-equals? (start-segment segment) vect-start)
(vector-equals? (end-segment segment) vect-end)

