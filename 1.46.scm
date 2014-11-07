(define (iterate-improve test improve)
  (lambda (init)
    (((lambda (y) (y y))
      (lambda (recur)
        (lambda (guess)
          (if (test guess)
            guess
            ((recur recur) (improve guess))
          )
        )
      )
     )
     init
    )
  )
)

(define (sqroot x)
  ((iterate-improve 
       (lambda (guess)
         (< (abs (- (square guess) x)) 0.00001)
       )
       (lambda (guess)
         (/ (+ guess
               (/ x guess)
            )
            2
         )
       )
    )
    1.0
  )
)
(sqroot 9)    ; 3.000000001396984
(sqroot 900)  ; 30.00000000000009

(define (fixed-point f init)
  ((iterate-improve
     (lambda (guess)
       (< (abs (- guess (f guess))) 0.00001)
     )
     (lambda (guess)
       (f guess)
     )
   )
   init
  )
)

(fixed-point (lambda (x) (+ 1 (/ 1 x))) 2.0)  ; 1.6180371352785146
