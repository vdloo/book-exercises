; f(n) = n                                  if n <  3
; f(n) = f(n - 1) + 2f(n - 2) + 3f(n-3)     if n >= 3

; computes f by means of a recursive process
(define (f n)
  (if (< n 3)
      n
      (+ (f (- n 1)) (* 2 (f (- n 2))) (* 3 (f (- n 3))))
  )
)

(f 0)   ; 0
(f 3)   ; 4
(f 5)   ; 25
(f 10)  ; 1892
(f 25)  ; 812934961

; computes f by means of an iterative process

; f(1) = 1
; f(2) = 2
; f(3) = f(n-1) + 2f(n-2) + 3f(n-3)     = f(2) + 2f(1) + 3f(0)    = 2 + 2*1 + 3*0       = 4
; f(4) = f(n-1) + 2f(n-2) + 3f(n-3)     = f(3) + 2f(2) + 3f(1)    = 4 + 2*2 + 3*1       = 11
; f(5) = f(n-1) + 2f(n-2) + 3f(n-3)     = f(4) + 2f(3) + 3f(2)    = 11 + 2*4 + 3*2      = 25
;
(define (iter n count prev1 prev2 prev3)
  (if (= count n) 
    prev1
    (iter 
      n 
      (+ count 1) 
      (+ (* 3 prev3) (* 2 prev2) prev1)
      prev1 
      prev2
    )
  )
)
(define (f n)
  (if (< n 3) n (iter n 2 2 1 0))
)

(f 0)   ; 0
(f 1)   ; 0
(f 2)   ; 0
(f 3)   ; 4
(f 5)   ; 25
(f 10)  ; 1892
(f 25)  ; 812934961
