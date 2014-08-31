(define (f g) (g 2))

(f square)

(f (lambda (z) (* z (+ z 1))))

; The procedure
(f f)
; results in "The object 2 is not applicable."
; This happens due to (f f) resulting in (f 2) and 2 is not a procedure


