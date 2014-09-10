(define (square x) (* x x))

(define (repeated f n)
  (if (> n 1)
    (repeated (lambda (x) (f (f x))) (- n 1))
    (lambda (x) (f x))
  )
)

(define (smooth f)
  (lambda (x) (/ (+ (f x)
                    (f (+ x dx))
                    (f (- x dx))
                 )
                 3
              )
  )
)

(define pi 3.1415926535897932384626433832795028841971693993751058)

(define dx 0.7)

(sin (/ pi 2)) ; 1
((smooth sin) (/ pi 2)) ; 0.84322
(sin pi) ; 1.22
((smooth sin) pi) ; 7.40148

(define (n-fold f n)
  (repeated (smooth f) n)
)

((n-fold sin 2) (/ pi 2)) ; 0.6297176112540723
