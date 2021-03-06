(define (cube x) (* x x x))
(define (p x) (- (* 3 x) (* 4 (cube x))))
(define (sine angle)
  (if (not (> (abs angle) 0.1))
      angle
      (p (sine (/ angle 3.0)))
  )
)
(sine 12.15)
; The procedure p is appplied 5 times when (sine 12.15) is evaluated
; (p (sine 4.05))
; (p (p (sine 1.35)))
; (p (p (p (sine 0.45))))
; (p (p (p (p (sine 0.15)))))
; (p (p (p (p (p (sine 0.05))))))
; (p (p (p (p (p 0.05)))))
; (p (p (p (p 0.1495))))
; (p (p (p 0.4351345505)))
; (p (p 0.9758465331678772))
; (p -.7895631144708228)
; -.39980345741334

; Every time the input angle is tripled, sine will be called one extra time. This means that both the order of growth in space and number of steps is theta of log(n). 
