; x -> f(g(x))

(define (square x) (* x x))

(define (inc x) (+ x 1))

(define (compose f g)
  (lambda (x) (f (g x)))
)

(define (repeated f n)
  (if (> n 1)
    (compose f (repeated f (- n 1)))
    f
  )
)

((repeated inc 2) 5) ; 7
((repeated inc 10) 10) ; 20
((repeated square 2) 5) ; 625
