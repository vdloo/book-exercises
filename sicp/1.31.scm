(define (self x) x)

(define (inc x) (+ 1 x ))

(define (product term a next b)
  (if (> a b)
    1
    (* (term a)
       (product term (next a) next b)
    )
  )
)

(define (factorial x)
  (product self 1 inc x)
)

(factorial 10)

; Wallis Formula defined as a recursive process

(define (johnwallis x)
  (define (term x)
    (/ (* 4 (* x x))
       (- (* 4 (* x x)) 1)
    )
  )
  (* 2.0 (product term 1 inc x))
)

(johnwallis 10000)

; Wallis Formula defined as an iterative process

(define (product term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter (next a) (* (term a) result))
    )
  )
  (iter a 1)
)

(johnwallis 10000)
