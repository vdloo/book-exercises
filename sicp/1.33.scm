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

(define (filt-accumulate combiner null-value term a next b filt)
  (define (filt-accumulate-iter a result)
    (if (> a b)
      result
      (if (filt a)
        (filt-accumulate-iter (next a) (combiner (term a) result))
        (filt-accumulate-iter (next a) result)
      )
    )
  )
  (filt-accumulate-iter a null-value)
)

(define (inc n) (+ n 1))

(define (sum-of-squared-primes a b)
  (filt-accumulate + 0 square a inc b prime?)
)

(sum-of-squared-primes 2 3)   ; 13
(sum-of-squared-primes 2 6)   ; 38
(sum-of-squared-primes 2 10)  ; 87

(define (gcd-euclid a b)
  (if (= b 0)
    a
    (gcd-euclid b (remainder a b))
  )
)

(define (identity x) x)

(define (prod-rel-prime n)
  (define (rel-prime? a)
    (= (gcd-euclid a n) 1)
  )
  (filt-accumulate * 1 identity 1 inc (- n 1) rel-prime?)
)

(prod-rel-prime 4)           ; 3
(prod-rel-prime 8)           ; 105
(prod-rel-prime 9)           ; 2240
