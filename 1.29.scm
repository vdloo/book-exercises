(define (cube x) (* x x x))

(define (sum term a next b)
  (if (> a b)
    0
    (+ (term a)
       (sum term (next a) next b)
    )
  )
)

(define (integral f a b dx)
  (define (add-dx x) (+ x dx))
  (* (sum f (+ a (/ dx 2.0)) add-dx b) dx)
)

(define (iseven n) (= (remainder n 2) 0))

(define (simpsons f a b n)
  (define calch (/ ( - b a) n))
  (define (plusone x) (+ x 1))
  (define (calcy k)
    (f (+ a (* k calch)))
  )
  (define (calcterm k)
    (* (calcy k)
      (if (not (iseven k))
          4
          (if (or (= k 0) (= k n))
              1
              2
          )
      )
    )
  )
  (* (/ calch
        3
     ) 
     (sum calcterm 0 plusone n)
  )
)

(integral cube 0 1 0.01)
(simpsons cube 0 1 100.0)
(integral cube 0 1 0.001)
(simpsons cube 0 1 1000.0)

; Simpson's Rule is indeed more accurate
