; x -> f(g(x))

(define (square x) (* x x))

(define (compose f g)
  (lambda (x) (f (g x)))
)

(define (repeated f n)
  (if (> n 1)
    (repeated (lambda (x) (f (f x))) (- n 1))
    (lambda (x) (f x))
  )
)

((repeated square 2) 5)
