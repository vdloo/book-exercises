(define (inc x)
  (+ x 1)
)
(define (dec x)
  (- x 1)
)

; This procedure is recursive, the inc procedure is deferred every time the function calls itself
; this results in (inc (+ (dec a b)) becoming (inc (inc (+ dec a b)) etc.

; (+ 4 5)
; (inc (+ (dec 4) 5))
; (inc (+ 3 5))
; (inc (inc (+ (dec 3) 5)))
; (inc (inc (+ 2 5)))
; (inc (inc (inc (+ (dec 2) 5))))
; (inc (inc (inc (+ 1 5))))
; (inc (inc (inc (inc (inc (+ 0 5)))))
; (inc (inc (inc (inc (inc 5)))))
; (inc (inc (inc (inc 5))))
; (inc (inc (inc 6)))
; (inc (inc 7))
; (inc 8)
; 9
;

(define (+ a b)
  (display b)
  (if (= a 0)
      b
      (inc (+ (dec a) b))
  )
)
(+ 4 5)

; This procedure is iterative because all the state variables are passed into the next iteration,
; there is no need for the interpreter to keep track of what happens outside of the current iteration. 
(define (+ a b)
  (if (= a 0)
      b
      (+ (dec a) (inc b))
  )
)
(+ 4 5)
