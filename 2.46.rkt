#lang sicp

(define (make-vect x y)
  (cons x y))

(define (xcor-vect vect)
  (car vect))

(define (ycor-vect vect)
  (cdr vect))

(define (proc-attrgetter proc attrgetter)
  (lambda (vect-a vect-b)
    (proc (attrgetter vect-a) (attrgetter vect-b))))

(define (compose-vect-operation proc)
  (lambda (vect-a vect-b)
    (make-vect
      ((proc-attrgetter proc xcor-vect) vect-a vect-b)
      ((proc-attrgetter proc ycor-vect) vect-a vect-b))))
  
(define (add-vect vect-a vect-b)
  ((compose-vect-operation +) vect-a vect-b))

(define (sub-vect vect-a vect-b)
  ((compose-vect-operation -) vect-a vect-b))

(define (scale-vect vect scale)
  (make-vect
    (* (xcor-vect vect) scale)
    (* (ycor-vect vect) scale)))

(define vect-a (make-vect 5 10))
vect-a
(define vect-b (make-vect 7 14))
vect-b
(define vect-c (add-vect vect-a vect-b))
vect-c
(define vect-d (sub-vect vect-b vect-a))
vect-d
(define vect-e (scale-vect vect-a 3))
vect-e
