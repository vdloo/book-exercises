(define (close-enough? x y)
  (> (abs (- x y)) 0.00001)
)

(define (average x y) (/ (+ x y) 2.0))

(define (search f neg-point pos-point)
  (let ((midpoint (average neg-point pos-point)))
    (if (close-enough? neg-point pos-point)
      midpoint
      (let ((test-value (f midpoint)))
            (cond ((positive? test-value)
                   (search f neg-point midpoint)
                  )
                  ((negative? test-value)
                   (search f midpoint pos-point)
                  )
                  (else midpoint)
            )
      )
    )
  )
)

(define (half-interval-method f a b)
  (let ((a-value (f a))
        (b-value (f b))
       )
       (cond ((and (negative? a-value) (positive? b-value))
              (search f a b)
             )
             ((and (negative? b-value) (positive? a-value))
              (search f b a)
             )
             (else
               (error "Values are not of opposite sign" a b)
             )
       )
   )
)
        
; approximate pie as the root between 2 and 5 of sin x = 0
(half-interval-method sin 2.0 4.0)

; search for a root of the equation x^3 - 2x - 3
(half-interval-method (lambda (x) (- (* x x x) (* 2 x) 3)) 1.0 2.0)

(define tolerance 0.00001)
(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance)
  )
  (define (try guess)
    (let  ((next (f guess)))
          (if (close-enough? guess next)
              next
              (try next)
          )
    )
  )
  (try first-guess)
)

; approximate the fixed point of the cosine starting with 1 as an initial approximation
(fixed-point cos 1.0)

; solution to the equation y = sin y + cos y
(fixed-point (lambda (y) (+ (sin y) (cos y))) 1.0)

; exercise 1.35: Show that the golden ratio phi is a fixed point of the transformation x -> 1 + 1/x
(fixed-point (lambda (x) (+ 1 (/ 1 x))) 2.0)
