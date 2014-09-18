(define (close-enough? x y)
  (> (abs (- x y)) 0.00001)
)

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

(define (average x y) (/ (+ y x) 2))

(define (average-damp f)
  (lambda (x) (average x (f x)))
)

(define (compose f g)
    (lambda (x) (f (g x)))
)

(define (repeated f n)
  (if (> n 1)
    (compose f (repeated f (- n 1)))
    f
  )
)

(define (nth-root x n)
  (define (transform n)
    (lambda (y) (/ x (expt y (- n 1))))
  )
  (fixed-point
    (average-damp
      (transform n)
    )
    1.0
  )
)

(nth-root 100 2) ; 10
(nth-root 1000 3) ; 10
; (nth-root 10000 4) ; infinite loop, fails to converge with only one average damp

(define (nth-root x n)
  (define (transform n)
    (lambda (y) (/ x (expt y (- n 1))))
  )
  (fixed-point
    ((repeated average-damp 2)
      (transform n)
    )
    1.0
  )
)

(nth-root 10000 4) ; 10
(nth-root 100000 5) ; 10
(nth-root 1000000 6) ; 10
(nth-root 10000000 7) ; 10
; (nth-root 100000000 8) ; infinite loop, fails to converge with two average damps

(define (nth-root x n)
  (define (transform n)
    (lambda (y) (/ x (expt y (- n 1))))
  )
  (fixed-point
    ((repeated average-damp 3)
      (transform n)
    )
    1.0
  )
)

(nth-root 100000000 8) ; 10
(nth-root 1000000000 9) ; 10
(nth-root 10000000000 10) ; 10
(nth-root 100000000000 11) ; 10
(nth-root 1000000000000 12) ; 10
(nth-root 10000000000000 13) ; 10
(nth-root 100000000000000 14) ; 10
(nth-root 1000000000000000 15) ; 10
;(nth-root 10000000000000000 16) ; infinite loop, fails to converge with three average damps

