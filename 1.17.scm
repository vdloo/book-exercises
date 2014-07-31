(define (mul a b)
    (if (= b 0)
        0
        (+ a (mul a (- b 1)))
    )
)

(define (double a)
  (mul a 2)
)

(define (mod-count a b c)
  (if (>= a b)
      (mod-count (- a b) b (+ 1 c))
      c
  )
)

(define (div a b)
  (mod-count a b 0)
)

(define (halve a)
  (div a 2)
)

(define (iseven n) (= (remainder n 2) 0))

(define (fast-mul a b)
  (cond ((= b 0) 0)
        ((= b 1) a)
        ((iseven b) (double (fast-mul a (halve b))))
        (else (+ a (fast-mul a (- b 1))))
  )
)

(fast-mul 100000 100000)
