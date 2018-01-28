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
    
(cont-frac (lambda (i) 1.0) 
           (lambda (i) 1.0) 
           10 ; k must be 10 in order to get an approximation that is accurate to 4 decimal places
)

; iterative version

(define (cont-frac n d k)
  (define (frac-iter i result)
    (if (= i 0)
      result
      (frac-iter (- i 1) (/ (n i) (+ (d i) result)))
    )
  )
  (frac-iter (- k 1) (/ (n k) (+ (d k))))
)

(cont-frac (lambda (i) 1.0) 
           (lambda (i) 1.0) 
           11
)
