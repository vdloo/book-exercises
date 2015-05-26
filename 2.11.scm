(define (make-interval a b) (cons a b))
(define (lower-bound x) (car x))
(define (upper-bound x) (cdr x))

; original definition of mul-interval from the book
;(define (mul-interval x y)
;  (let ((p1 (* (lower-bound x) (lower-bound y)))
;        (p2 (* (lower-bound x) (upper-bound y)))
;        (p3 (* (upper-bound x) (lower-bound y)))
;        (p4 (* (upper-bound x) (upper-bound y))))
;    (make-interval (min p1 p2 p3 p4)
;                   (max p1 p2 p3 p4))))

(define (mul-interval x y)
     (let ((x1 (lower-bound x))
           (x2 (upper-bound x))
           (y1 (lower-bound y))
           (y2 (upper-bound y)))
     (cond 
       ((and (< x1 0)  ; 1 -- --
             (< x2 0) 
             (< y1 0)
             (< y2 0))
        (make-interval (* x2 y2) (* x1 y1)))
       ((and (< x1 0)  ; 2 -- -+
             (< x2 0)
             (< y1 0)
             (>= y2 0))
        (make-interval (* x1 y2) (* x1 y1)))
       ((and (< x1 0)  ; 3 -- ++
             (< x2 0)
             (>= y1 0)
             (>= y2 0))
        (make-interval (* x1 y2) (* x2 y1)))
       ((and (< x1 0)  ; 4 -+ ++
             (>= x2 0)
             (>= y1 0)
             (>= y2 0))
        (make-interval (* x1 y2) (* x2 y2)))
       ((and (>= x1 0)  ; 5 ++ ++
             (>= x2 0)
             (>= y1 0)
             (>= y2 0))
        (make-interval (* x1 y1) (* x2 y2)))
       ((and (>= x1 0)  ; 6 ++ -+ q
             (>= x2 0)
             (< y1 0)
             (>= y2 0))
        (make-interval (* x2 y1) (* x2 y2)))
       ((and (>= x1 0)  ; 7 ++ -- q
             (>= x2 0)
             (< y1 0)
             (< y2 0))
        (make-interval (* x2 y1) (* x1 y2)))
       ((and (< x1 0)  ; 8 -+ --
             (>= x2 0)
             (< y1 0)
             (< y2 0))
        (make-interval (* x2 y1) (* x1 y1)))
       ((and (< x1 0)  ; 9 -+ -+ q
             (>= x2 0)
             (< y1 0)
             (>= y2 0))
        (make-interval (min (* x2 y1) (* x1 y2))
                       (max (* x1 y1) (* x2 y2))))
       (else (error "fell through the cond, that should never happen!")))))

(define interval1 (make-interval 10 20))
(define interval2 (make-interval -10 20))
(define interval3 (make-interval -10 -20))

(mul-interval interval1 interval1)  ; (100 . 400)
(mul-interval interval1 interval2)  ; (-200 . 400)
(mul-interval interval1 interval3)  ; (-200 . -200)

(mul-interval interval2 interval1) ; (-200 . 400)
(mul-interval interval2 interval2) ; (-200 . 400)
(mul-interval interval2 interval3) ; (-200 . 100)

(mul-interval interval3 interval1) ; (-200 . -200)
(mul-interval interval3 interval2) ; (-200 . 100)
(mul-interval interval3 interval3) ; (400 . 100)
