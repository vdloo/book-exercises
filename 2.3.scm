(define (make-point x y)
  (cons x y))

(define (x-point p)
  (car p))

(define (y-point p)
  (cdr p))

(define (make-segment x y)
  (cons x y))

(define (start-segment s)
  (car s))

(define (end-segment s)
  (cdr s))

(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(define (print-segment s)
  (newline)
  (display "Segment consists of the following two points")
  (newline)
  (display "x-point: ")
  (print-point (start-segment s))
  (newline)
  (display "y-point: ")
  (print-point (end-segment s)))

(define (point-compare a b)
  (and
    (= (x-point a) (x-point b))
    (= (y-point a) (y-point b))))

(define (touch a b)
  (+ 
    (if (point-compare (start-segment a) (start-segment b)) 1 0)
    (if (point-compare (start-segment a) (end-segment b)) 1 0)
    (if (point-compare (end-segment a) (start-segment b)) 1 0)
    (if (point-compare (end-segment a) (end-segment b)) 1 0)))

(define (check-if-solid-rectangle a b c d)
  (= (+ (touch a b) 
     (touch b c) 
     (touch c d) 
     (touch d a) 
     (touch a c)
     (touch b d)) 4))

(define (make-rectangle seg-a seg-b seg-c seg-d)
  (if (check-if-solid-rectangle seg-a seg-b seg-c seg-d)
    (cons 
      (cons seg-a seg-b)    ; left and bottom
      (cons seg-c seg-d))   ; right and top
    (begin 
      (newline)
      (display "Not a valid rectangle, points don't connect")
      #f)))

(define (get-rectangle-segment r x)
  (cond ((= x 1) (car (car r)))
        ((= x 2) (car (cdr r)))
        ((= x 3) (cdr (car r)))
        ((= x 4) (cdr (cdr r)))))

(define (print-rectangle r)
  (newline)
  (display "Rectangle consists of the following four segments")
  (print-segment (get-rectangle-segment r 1))
  (print-segment (get-rectangle-segment r 2))
  (print-segment (get-rectangle-segment r 3))
  (print-segment (get-rectangle-segment r 4)))


(define point-a (make-point 0 0))
(define point-b (make-point 0 2))
(define segment-a (make-segment point-a point-b))
(define point-c (make-point 0 2))
(define point-d (make-point 2 2))
(define segment-b (make-segment point-c point-d))
(define point-e (make-point 2 2))
(define point-f (make-point 2 0))
(define segment-c (make-segment point-e point-f))
(define point-g (make-point 2 0))
(define point-h (make-point 0 0))
(define segment-d (make-segment point-g point-h))

(define r (make-rectangle 
  segment-a
  segment-b
  segment-c
  segment-d))


(define (get-distance-segment s)
  (let (
        (xdist (abs (- (x-point (start-segment s))
                        (x-point (end-segment s)))))
        (ydist (abs (- (y-point (start-segment s))
                        (y-point (end-segment s))))))
        (sqrt (+ (expt xdist 2) (expt ydist 2)))))

(define (get-rectangle-perimeter r)
  (+ 
    (get-distance-segment (get-rectangle-segment r 1))
    (get-distance-segment (get-rectangle-segment r 2))
    (get-distance-segment (get-rectangle-segment r 3))
    (get-distance-segment (get-rectangle-segment r 4))))


(define (get-rectangle-area r)
  (*
    (get-distance-segment (get-rectangle-segment r 1))
    (get-distance-segment (get-rectangle-segment r 2))))

; Create and print rectangle in a plane, calculate primeter and area
(define r (make-rectangle 
  segment-a
  segment-b
  segment-c
  segment-d))
(print-rectangle r)
(get-rectangle-perimeter r)
(get-rectangle-area r)

; Re-implement the representation for rectangles to see if the abstraction barriers are suitable (perimeter and area should still work)
; Note: better would be to abstract get-rectangle-perimeter and get-rectangle-segment to the point where they can also handle a rectangle
; object where only one horizontal and one vertical segment is stored, the current implementation also allows for the shape to be a 
; trapezoid. But for the sake of this exercise I found switching up the sides and top/bottom enough to demonstrate the abstraction barriers.
(define (make-rectangle seg-a seg-b seg-c seg-d)
  (if (check-if-solid-rectangle seg-a seg-b seg-c seg-d)
    (cons 
      (cons seg-c seg-d)    ; top and bottom
      (cons seg-a seg-b))   ; sides
    (begin 
      (newline)
      (display "Not a valid rectangle, points don't connect")
      #f)))

; Create and print rectangle in a plane, calculate primeter and area
(define r (make-rectangle 
  segment-a
  segment-b
  segment-c
  segment-d))
(print-rectangle r)
(get-rectangle-perimeter r)
(get-rectangle-area r)
