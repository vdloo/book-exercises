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
    (abs (- x y))
    0.1
  )
)

(define (cube-iter x y yprev)
  (if (good-enough y yprev)
    y
    (cube-iter x (bettercube x y) y)
  )
) 

(define (cuberoot x)
  (cube-iter x 1.0 0)
)

(cuberoot 2)      ;	1.2599  procedure returns 1.2638888888888888
(cuberoot 27)     ; 3       procedure returns 3.001274406506175
(cuberoot 200000) ; 58.480  procedure returns 58.4803547787669
