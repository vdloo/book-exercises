(define (iseven n) (= (remainder n 2) 0))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((iseven exp) (remainder (square (expmod base (/ exp 2) m)) m))
        (else (remainder (* base (expmod base (- exp 1) m)) m))
  )
)

(define (carmichael-iter n a s)
  (if s
    (if (< a n)
      (carmichael-iter n (+ a 1) (= (expmod a n n) a))
      #t
    )
    #f
  )
)

(define (carmichael n)
  (carmichael-iter n 1 #t)
)

(carmichael 101)
(carmichael 561)
(carmichael 1105)
(carmichael 1729)
(carmichael 2465)
(carmichael 2821)
(carmichael 6601)
