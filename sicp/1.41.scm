(define (inc n) (+ n 1))

(define (double f)
  (lambda (x) (f (f x)))
)

((double inc) 1) ; 3
(((double double) inc) 1) ; 5
(((double (double double)) inc) 1) ; 17
