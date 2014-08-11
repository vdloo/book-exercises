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

(define (prime? n)
  (= n (smallest-divisor n))
)

(define (time-prime-test n)
  (start-prime-test n (runtime))
)

(define (start-prime-test n start-time)
  (if (prime? n)
    (report-prime n (- (runtime) start-time))
  )
)

(define (report-prime n elapsed-time)
  (newline)
  (display n)
  (display " *** ")
  (display elapsed-time)
)

(define (iseven n) (= (remainder n 2) 0))

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

; without next procedure
; (search-for-primes 1000000)
; 1000003 *** 0.
; 1000033 *** 0.
; 1000037 *** 0.
;
; (search-for-primes 10000000000)
; 10000000019 *** .2
; 10000000033 *** .2
; 10000000061 *** .19999999999999996

; (search-for-primes 100000000000)
; 100000000003 *** .6799999999999999    
; 100000000019 *** .6400000000000001
; 100000000057 *** .5800000000000001

; with next procedure
; (search-for-primes 1000000)
; 1000003 *** 0.
; 1000033 *** 0.
; 1000037 *** 0.

; (search-for-primes 10000000000)
; 10000000019 *** .11
; 10000000033 *** .12
; 10000000061 *** .10999999999999999

; (search-for-primes 100000000000)
; 100000000003 *** .35
; 100000000019 *** .38
; 100000000057 *** .34999999999999987

; The program runs now (almost) twice as fast so the expectation is correct. It is not exactly two because of i.a. the additional overhead of the next procedure, but this is a marginal difference.
