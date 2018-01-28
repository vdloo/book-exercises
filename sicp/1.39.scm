; recursive version

(define (cont-frac n d k)
  (define (frac i)
    (if (> k i)
      (/ (n i) (+ (d i) (frac (+ i 1))))
      (/ (n i) (d i))
    )
  )
  (frac 1.0)
)
    
(define (tan-cf x k)
  (cont-frac 
             (lambda (i) (if (> i 1) 
                           (* x x -1)
                           x
                         )
             )
             (lambda (i) (if (> i 1)
                           (+ 1 (* (- i 1) 2)) 
                           1
                         )
             )
             k
  )
)

(define pi (/ 355 113))

(tan (/ pi 6))
(tan-cf (/ pi 6) 10)
(tan (/ pi 4))
(tan-cf (/ pi 4) 10)
(tan (/ pi 3))
(tan-cf (/ pi 3) 10)
