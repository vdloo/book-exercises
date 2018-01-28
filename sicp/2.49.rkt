#lang racket/base
(#%require sicp-pict)

(define (make-vect x y)
  (cons x y))

(define (xcor-vect vect)
  (car vect))

(define (ycor-vect vect)
  (cdr vect))

(define start-frame 0.00)
(define end-frame 0.99)

(define (avg val1 val2)
  (/ (+ val1 val2) 2))

(define middle-frame (avg start-frame end-frame))

(define (make-segment vect-origin-to-start vect-origin-to-end)
  (cons vect-origin-to-start vect-origin-to-end))

(define outline-painter
  (segments->painter
   (list
    (make-segment
     (make-vect start-frame start-frame)
     (make-vect start-frame end-frame))
    (make-segment
     (make-vect start-frame start-frame)
     (make-vect end-frame start-frame))
    (make-segment
     (make-vect end-frame start-frame)
     (make-vect end-frame end-frame))
    (make-segment
     (make-vect start-frame end-frame)
     (make-vect end-frame end-frame)))))

(paint outline-painter)

(define x-painter
  (segments->painter
   (list
    (make-segment
     (make-vect start-frame start-frame)
     (make-vect end-frame end-frame))
    (make-segment
     (make-vect start-frame end-frame)
     (make-vect end-frame start-frame)))))

(paint x-painter)

(define diamond-painter
  (segments->painter
   (list
    (make-segment
     (make-vect start-frame middle-frame)
     (make-vect middle-frame start-frame))
    (make-segment
     (make-vect start-frame middle-frame)
     (make-vect middle-frame end-frame))
    (make-segment
     (make-vect middle-frame end-frame)
     (make-vect end-frame middle-frame))
    (make-segment
     (make-vect end-frame middle-frame)
     (make-vect middle-frame start-frame)))))

(paint diamond-painter)

(define wave-painter
  (segments->painter
   (list
    (make-segment
     (make-vect 0.00 0.80)
     (make-vect 0.25 0.60))
    (make-segment
     (make-vect 0.25 0.60)
     (make-vect 0.30 0.65))
    (make-segment
     (make-vect 0.30 0.65)
     (make-vect 0.35 0.65))
    (make-segment
     (make-vect 0.35 0.65)
     (make-vect 0.30 0.85))
    (make-segment
     (make-vect 0.30 0.85)
     (make-vect 0.35 0.99))
    (make-segment
     (make-vect 0.55 0.99)
     (make-vect 0.60 0.85))
    (make-segment
     (make-vect 0.60 0.85)
     (make-vect 0.55 0.65))
    (make-segment
     (make-vect 0.55 0.65)
     (make-vect 0.75 0.65))
    (make-segment
     (make-vect 0.75 0.65)
     (make-vect 0.99 0.40))
    (make-segment
     (make-vect 0.99 0.30)
     (make-vect 0.60 0.50))
    (make-segment
     (make-vect 0.60 0.50)
     (make-vect 0.80 0.00))
    (make-segment
     (make-vect 0.70 0.00)
     (make-vect 0.50 0.35))
    (make-segment
     (make-vect 0.50 0.35)
     (make-vect 0.30 0.00))
    (make-segment
     (make-vect 0.10 0.00)
     (make-vect 0.30 0.45))
    (make-segment
     (make-vect 0.30 0.45)
     (make-vect 0.25 0.50))
    (make-segment
     (make-vect 0.25 0.50)
     (make-vect 0.15 0.45))
    (make-segment
     (make-vect 0.15 0.45)
     (make-vect 0.00 0.60)))))

(paint wave-painter)
