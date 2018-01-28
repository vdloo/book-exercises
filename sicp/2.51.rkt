#lang racket/base
(#%require sicp-pict)

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

(define (sub-vect vect-a vect-b)
  ((compose-vect-operation -) vect-a vect-b))

(define (transform-painter painter origin corner1 corner2)
  (lambda (frame)
    (let ((m (frame-coord-map frame)))
      (let ((new-origin (m origin)))
        (painter
         (make-frame new-origin
                     (sub-vect (m corner1) new-origin)
                     (sub-vect (m corner2) new-origin)))))))

; a
(define (below-1 painter1 painter2)
  (lambda (frame)
      ((transform-painter painter1
                       (make-vect 0.0 0.0)   ; new origin
                       (make-vect 1.0 0.0)   ; new end of edge1
                       (make-vect 0.0 0.5))  ; new end of edge2
       frame)
      ((transform-painter painter2
                       (make-vect 0.0 0.5)   ; new origin
                       (make-vect 1.0 0.5)   ; new end of edge1
                       (make-vect 0.0 1.0))  ; new end of edge2
       frame)))

(paint (below-1 einstein einstein))

; b
(define (rotate-270 painter)
  (transform-painter painter
                     (make-vect 0.0 1.0)   ; new origin
                     (make-vect 0.0 0.0)   ; new end of edge1
                     (make-vect 1.0 1.0))) ; new end of edge2

(define (rotate-90 painter)
  (transform-painter painter
                     (make-vect 1.0 0.0)   ; new origin
                     (make-vect 1.0 1.0)   ; new end of edge1
                     (make-vect 0.0 0.0))) ; new end of edge2

(define (below-2 painter1 painter2)
  (rotate-90 (beside (rotate-270 painter1) (rotate-270 painter2))))

(paint (below-2 einstein einstein))