#lang sicp
(#%require sicp-pict)

(define (split pos-large pos-small)
  (define (mul-split painter n)
    (if (= n 0)
        painter
        (let ((smaller (mul-split painter (- n 1))))
          (pos-large painter (pos-small smaller smaller)))))
  mul-split)

(define right-split (split beside below))

(paint (right-split einstein 1))

(define up-split (split below beside))

(paint (up-split einstein 1)) 

