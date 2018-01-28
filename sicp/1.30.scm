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

(integral cube 0 1 0.01)
(integral cube 0 1 0.001)

(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (+ (term a) result))
    )
  )
  (iter a 0)
)

(integral cube 0 1 0.01)
(integral cube 0 1 0.001)
