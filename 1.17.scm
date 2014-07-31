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

; mul 4 4 16
(mul 4 4)

; double 8 16
(double 8)

; div 16 4 4
(div 20 4)

; halve 16 2 8
(halve 16)
