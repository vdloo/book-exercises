; x1 = interval 1 lower bound
; x2 = interval 1 upper bound
; y1 = interval 1 lower bound
; y2 = interval 1 upper bound

; (* interval1 interval2)
; (* (x1 . x2) (y1 . y2))
; ((* x1 y1) . (* x2 y2)) because we can assume all numbers are positive

; c1 = center of interval 1
; t1 = percentual tolerance of interval 1
; c2 = center of interval 2
; t2 = percentual tolerance of interval 2

; ((* c1 c2 (- 1 (/ t1 100)) (- 1 (/ t2 100))) . (* c1 c2 (+ 1 (/ t1 100)) (+ 1 (/ t2 100))))

; ((+ (- (/ (* c1 c2 t1 t2) 10000) (/ (* c1 c2 t1) 100) (/ (* c1 c2 t2) 100)) (* c1 c2)) .
;  (+ (/ (* c1 c2 t1 t2) 10000) (/ (* c1 c2 t1) 100) (/ (* c1 c2 t2) 100) (* c1 c2)))

; we want to show a simple formula in the case of small percentage tolerances so we can ignore the / 10000 parts

; ((+ (- (/ (* c1 c2 t1) 100) (/ (* c1 c2 t2) 100)) (* c1 c2)) . (+ (/ (* c1 c2 t1) 100) (/ (* c1 c2 t2) 100) (* c1 c2)))
