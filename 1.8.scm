; Newton's method for cube roots
(define (bettercube x y)
	(/	(+	(/	x
							(square y)
					)
					(+ y y)
			)
			3
	)
)

(define (good-enough x y)
	(< 
		(- (bettercube x y) x)
		0.001
	)
)

(define (cube-iter x y)
	(if	(good-enough x y)
			(bettercube x y)
			x
	)
)

(define (cuberoot x)
	(cube-iter x 1)
)

(cuberoot 81) ; 9
