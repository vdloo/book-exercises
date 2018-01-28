(define (self x) x)

(define (inc x) (+ 1 x ))

; recursive process
(define (accumulate combiner null-value term a next b)
  (if (> a b)
    null-value
    (combiner (term a)
       (accumulate combiner null-value term (next a) next b)
    )
  )
)

; sum 10
(accumulate + 0 self 1 inc 10)

; factorial 10
(accumulate * 1 self 1 inc 10)

; iterative process
(define (accumulate combiner null-value term a next b)
  (define (accumulate-iter a result)
    (if (> a b)
      result
      (accumulate-iter (next a) (combiner (term a) result))
    )
  )
  (accumulate-iter a null-value)
)

; sum 10
(accumulate + 0 self 1 inc 10)

; factorial 10
(accumulate * 1 self 1 inc 10)
