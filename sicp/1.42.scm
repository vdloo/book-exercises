; x -> f(g(x))

(define (square x) (* x x))

(define (inc n) (+ n 1))

(define (compose f g)
  (lambda (x) (f (g x)))
)

((compose square inc) 6)
