(define (make-interval a b) (cons a b))
(define (lower-bound x) (car x))
(define (upper-bound x) (cdr x))

(define interval1 (make-interval 10 20))
(define interval2 (make-interval 30 50))

(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))

(define (sub-interval x y)
  (make-interval (- (lower-bound x) (lower-bound y))
                 (- (upper-bound x) (upper-bound y))))

(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

(define (div-interval x y)
  (mul-interval x
                (make-interval (/ 1.0 (upper-bound y))
                               (/ 1.0 (lower-bound y)))))

(define (width x)
  (/ (abs (- (lower-bound x) (upper-bound x))) 2))

(width interval1)  ; is 5
(width interval2)  ; is 10

; As can be seen in the examples below, the width of the difference of two
; intervals is a function of addition and substraction, but not of
; multiplication and division. 

; width of interval1 + width of interval 2 is 15
(width (add-interval interval1 interval2))  ; checks out, is 15
; width of interval1 - width of interval 2 is 5
(width (sub-interval interval1 interval2))  ; checks out, is 5

; width of interval1 * width of interval 2 is 15
(width (mul-interval interval1 interval2))  ; doesn't check out, is 350
; width of interval1 / width of interval 2 is 0.5
(width (div-interval interval1 interval2))  ; doesn't check out, is .2333333333333333
