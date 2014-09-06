(define tolerance 0.00001)

(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance)
  )
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next)
      )
    )
  )
  (try first-guess)
)

(define (average-damp f)
  (lambda (x) (average x (f x)))
)

(define dx 0.00001)

(define (deriv g)
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
       dx
    )
  )
)

(define (newton-transform g)
  (lambda (x)
    (- x (/ (g x) ((deriv g) x)))
  )
)

(define (newtons-method g guess)
  (fixed-point (newton-transform g) guess)
)

(define (cubic a b c)
  (lambda (x)
    (+ (* x x x) (* a x x) (* b x) c)
  )
)

(newtons-method (cubic 3 5 7) 1) ; should be -2.1795
