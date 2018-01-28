(define (cons x y)
  (* (expt 2 x)(expt 3 y)))

(define (divide-until-decimal m d)
  (if (= (gcd m d) 1)
    m
    (divide-until-decimal (/ m d) d)))

(define (unpack-product-of-exponents m b1 b2)
  (/ (log (divide-until-decimal m b2)) (log b1)))

(define (car m)
  (unpack-product-of-exponents m 2 3))

(define (cdr m)
  (unpack-product-of-exponents m 3 2))

; Create cons of 5 and 7 (2^5 + 3^7 = 69984)
(define m (cons 5 7))


; The car of m is 5
(car m)

; The cdr of m is 7
(cdr m)
