(define (make-interval a b) (cons a b))
(define (lower-bound x) (car x))
(define (upper-bound x) (cdr x))

(define interval1 (make-interval 0 0))
(define interval2 (make-interval 30 50))

(define (mul-interval x Y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

(define (interval-not-zero? x)
  (<= 0 (abs (- (lower-bound x)
                (upper-bound x)))))

(define (div-interval x y)
  (if (interval-not-zero? y)
      (mul-interval x
                    (make-interval (/ 1.0 (upper-bound y))
                                   (/ 1.0 (lower-bound y)))))
      (error "Interval of divisor spans zero!"))

(div-interval interval1 interval2)
