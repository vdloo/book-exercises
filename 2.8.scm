(define (make-interval a b) (cons a b))
(define (lower-bound x) (car x))
(define (upper-bound x) (cdr x))

(define interval1 (make-interval 1 2))
(define interval2 (make-interval 3 5))

; The difference between intervals would be that the minimum value of the difference is the difference between the two lower bounds and the maximum value is the difference between the two upper bounds.

(define (sub-interval x y)
  (make-interval (- (lower-bound x) (lower-bound y))
                 (- (upper-bound x) (upper-bound y))))

(sub-interval interval1 interval2) ; (-2 . -3)
