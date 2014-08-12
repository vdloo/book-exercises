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

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((iseven exp) (remainder (square (expmod base (/ exp 2) m)) m))
        (else (remainder (* base (expmod base (- exp 1) m)) m))
  )
)

(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)
  )
)

(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a)
  )
  (try-it (+ 1 (random (- n 1))))
)

(define (time-prime-test n)
  (start-prime-test n (runtime))
)

(define (start-prime-test n start-time)
  (if (fast-prime? n 1000)
    (report-prime n (- (runtime) start-time))
  )
)

(define (report-prime n elapsed-time)
  (newline)
  (display n)
  (display " *** ")
  (display elapsed-time)
)

(define (search-for-primes-iter n amount)
    (begin
      (time-prime-test n)
      (search-for-primes-iter (+ n 2) amount)
    )
)

(define (search-for-primes thresh)
  (search-for-primes-iter 
    (if (iseven thresh)
      (+ thresh 1)
      thresh
    )
    thresh
  )
)

; The fast-prime? procedure is expected to test primes near 1,000,000 log(n) as fast as near 1,000.

; without fast-prime? procedure

; (search-for-primes 100000000000)
; 100000000003 *** .35
; 100000000019 *** .38
; 100000000057 *** .34999999999999987

; with fast-prime? procedure

; (search-for-primes 100000000000)
; 100000000003 *** 0.
; 100000000019 *** 0.
; 100000000057 *** 0.

; (search-for-primes 100000000000000000000000000)
; 100000000000000000000000067 *** .36
; 100000000000000000000000123 *** .33999999999999997
; 100000000000000000000000127 *** .3400000000000001

; (search-for-primes 1000000000000000000000000000)
; 1000000000000000000000000103 *** .34
; 1000000000000000000000000279 *** .34
; 1000000000000000000000000283 *** .3400000000000001

; Because computers are really really really fast these days, it is hard to see a significat increase in time spent calculating the prime numbers with such a fast algorithm. There is an algorithmic time increase because when the prime range increases by factor 10, the time spent calculating barely increases at all.

