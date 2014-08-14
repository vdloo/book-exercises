(define (divides? a b)
  (= (remainder b a) 0)
)

(define (next n)
  (if (= n 2)
    3
    (+ n 2)
  )
)

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (next test-divisor)))
  )
)

(define (smallest-divisor n)
  (find-divisor n 2)
)

(define (iseven n) (= (remainder n 2) 0))

(define (milrab-sqtest a b)
  (and
    (and 
      (not(= a 1)) 
      (not(= a (- b 1)))
    )
    (= (remainder (* a a) b) 1)
  )
)


(define (square-milrab a b)
  (if (milrab-sqtest a b)
    0
    (remainder (* a a) b)
  )
)


(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((iseven exp) (square-milrab (expmod base (/ exp 2) m) m))
        (else (remainder (* base (expmod base (- exp 1) m)) m))
  )
)

(define (miller-rabin-test n)
  (define (try-it a)
    (= (expmod a n n) a)
  )
  (try-it (+ 1 (random (- n 1))))
)

(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((miller-rabin-test n) (fast-prime? n (- times 1)))
        (else false)
  )
)

(define (miller-rabin n)
  (fast-prime? n 1000)
)

(miller-rabin 7)
(miller-rabin 561)
(miller-rabin 1105)
(miller-rabin 1729)
(miller-rabin 2465)
(miller-rabin 2821)
(miller-rabin 6601)
(miller-rabin 7919)

