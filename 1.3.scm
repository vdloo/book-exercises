(define (square x) (* x x))
; if x is at least bigger than one of the others return the square of x, else 0
(define (input x y z)
  	(if (or (> x y) (> x z))
		(square x)
		0
	)
)
; run input in three different orders
(define (procedure x y z) 
  	(+ (input x y z)
	   (input y x z)
	   (input z y x)
	)
)

(procedure 1 2 3) ; should be 4 + 9 = 13
(procedure 6 5 4) ; should be 36 + 25 = 61
(procedure 8 7 9) ; should be 64 + 81 = 145
