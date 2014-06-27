(define (inc x)
  (+ x 1)
)
(define (dec x)
  (- x 1)
)

; The first process is recursive, the inc procedure is deferred every time the function calls itself
; this results in (inc (add (dec a b)) becoming (inc (inc (add dec a b)) etc.

; (add 4 5)
; (inc (add (dec 4) 5))
; (inc (add 3 5))
; (inc (inc (add (dec 3) 5)))
; (inc (inc (add 2 5)))
; (inc (inc (inc (add (dec 2) 5))))
; (inc (inc (inc (add 1 5))))
; (inc (inc (inc (inc (add (dec 1) 5)))))
; (inc (inc (inc (inc (add 0 5)))))
; (inc (inc (inc (inc 5))))
; (inc (inc (inc 6)))
; (inc (inc 7))
; (inc 8)
; 9

(define (add a b)
  (display b)
  (if (= a 0)
      b
      (inc (add (dec a) b))
  )
)
(add 4 5)

; The second process is iterative because all the state variables are passed into the next iteration,
; there is no need for the interpreter to keep track of what happens outside of the current iteration. 

; (add 4 5)
; (add (dec 4) (inc 5))
; (add 3 6)
; (add (dec 3) (inc 6))
; (add 2 7)
; (add (dec 2) (inc 7))
; (add 1 8)
; (add (dec 1) (inc 8))
; (add 0 9)
; 9
;
(define (add a b)
  (if (= a 0)
      b
      (add (dec a) (inc b))
  )
)
(add 4 5)

; Both procedures are recursive because they refer to themselves, however the difference is that the first
; procedure shows an implementation of a recursive process and the second procedure displays an implementation 
; of an iterative process (which makes it tail-recursive). 
