(define (divides? a b)
  (= (remainder b a) 0)
)

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))
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

; (search-for-primes 1000)
; 1009 *** 0.
; 1013 *** 0.
; 1019 *** 0.

; (search-for-primes 10000)
; 10007 *** 0.
; 10009 *** 0.
; 10037 *** 0.
;
; (search-for-primes 100000)
; 100003 *** 0.
; 100019 *** 0.
; 100043 *** 0.
;
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
;
; 0.2 * sqrt(10) = 0.632456 so the sqrt(n) prediction is correct. 
; The result is compatible with the notion that programs on this machine run in time proportional to
; the number of steps required for the computation.

