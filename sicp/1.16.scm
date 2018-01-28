(define (square x) (* x x))
(define (iseven n) (= (remainder n 2) 0))
(define (fast-exp-r b n a)
  (cond ((= n 0) a)
        ((iseven n) (fast-exp-r (square b) (/ n 2) a))
        (else (fast-exp-r b (- n 1) (* b a)))
  )
)
(define (fast-exp b n)
  (fast-exp-r b n 1)
)

(fast-exp 5 10)   ; 9765625
(fast-exp 10 10)  ; 10000000000
(fast-exp 10 5)   ; 100000

