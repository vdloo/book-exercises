(define (close-enough? x y)
  (> (abs (- x y)) 0.00001)
)

(define (average x y) (/ (+ x y) 2.0))

(define tolerance 0.00001)

(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance)
  )
  (define (try guess)
    (newline)
    (display guess)
    (let  ((next (f guess)))
          (if (close-enough? guess next)
              next
              (try next)
          )
    )
  )
  (try first-guess)
)

; solution to x^x = 1000
(fixed-point (lambda (x) (/ (log 1000) (log x))) 5.0)

; with average damping
(fixed-point (lambda (x) (average x (/ (log 1000) (log x)))) 5.0)
