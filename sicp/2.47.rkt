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

(define vect-a (make-vect 0 0))
(define vect-b (make-vect 0 5))
(define vect-c (make-vect 5 0))

(define (make-frame1 origin edge1 edge2)
  (list origin edge1 edge2))

(define frame1 (make-frame1 vect-a vect-b vect-c))

(define (get-frame1-origin-vector frame)
  (car frame))

(define (get-frame1-edge1-vector frame)
  (cadr frame))

(define (get-frame1-edge2-vector frame)
  (caddr frame))

(vector-equals? (get-frame1-origin-vector frame1) vect-a)
(vector-equals? (get-frame1-edge1-vector frame1) vect-b)
(vector-equals? (get-frame1-edge2-vector frame1) vect-c)

(define (make-frame2 origin edge1 edge2)
  (cons origin (cons edge1 edge2)))

(define frame2 (make-frame2 vect-a vect-b vect-c))

(define (get-frame2-origin-vector frame)
  (car frame))

(define (get-frame2-edge1-vector frame)
  (cadr frame))

(define (get-frame2-edge2-vector frame)
  (cddr frame))

(vector-equals? (get-frame2-origin-vector frame2) vect-a)
(vector-equals? (get-frame2-edge1-vector frame2) vect-b)
(vector-equals? (get-frame2-edge2-vector frame2) vect-c)

