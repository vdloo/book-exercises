(define (make-interval a b) (cons a b))
(define (lower-bound x) (car x))
(define (upper-bound x) (cdr x))

(define (make-center-percent center percent)
  (let ((percent-decimal (/ percent 100)))
    (make-interval (* center (- 1.0 percent-decimal)) 
                   (* center (+ 1.0 percent-decimal)))))
(define (center i)
   (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (percent i)
  (let ((base (center i)))
    (* 100 (/ (abs (- (upper-bound i) base)) base))))

(define interval1 (make-center-percent 100 10))
interval1  ; ( 90 . 110 )

(center interval1)  ; 100

(percent interval1) ; 10
