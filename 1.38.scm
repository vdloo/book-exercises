(define (fractionibus n)
  (if (and (= 0 (remainder (- n 2) 3)) (< 1 n))
    (* (round (/ n 3)) 2)
    1
  )
)


(define (cont-frac n d k)
  (define (frac i)
    (if (> k i)
      (/ (n 1) (+ (d i) (frac (+ i 1))))
      (/ (n 1) (d i))
    )
  )
  (frac 1.0)
)
    
(define e
  (+ (cont-frac (lambda (i) 1.0) 
                fractionibus
             10 
     )
     2
  )
)
e

