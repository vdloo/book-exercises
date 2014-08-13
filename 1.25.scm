; The procedure
(define (expmod base exp m)
  (remainder (fast-exp base exp) m)
)

; is slower than the procedure
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((iseven exp) (remainder (square (expmod base (/ exp 2) m)) m))
        (else (remainder (* base (expmod base (- exp 1) m)) m))
  )
)

; because it doesn't have to deal with numbers much larger than m.
; It is straight forward that there comes a point where larger numbers
; take longer to compute than smaller ones, the cutoff for that to happen 
; will probably be around what fits in the 32 bit integer but that's all 
; taken care of by the interpreter. 
