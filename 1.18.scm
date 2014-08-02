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

(define (fast-mul-r a b s)
  (cond ((= b 0) s)
        ((iseven b) (fast-mul-r (double a) (halve b) s))
        (else (fast-mul-r a (- b 1) (+ a s)))
  )
)

(define (fast-mul a b)
  (fast-mul-r a b 0)
)

(fast-mul 100000 100000)
(fast-mul 4 4)
(fast-mul 16 8)
