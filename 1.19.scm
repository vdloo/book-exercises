; T:      A <- A + B
;         B <- A
;
; Tpq:    A1 <- BQ + AQ + AP
;         B1 <- BP + AQ
;       
;         A2 <- (BP + AQ)P + (BQ + AQ + AP)Q + (BQ + AQ + AP)P
;         B2 <- (BP + AQ)P + (BQ + AQ + AP)Q
;
; Tp'q':  A <- BQ' + AQ' + AP'
;         B <- BP' + AQ'
;
;
; B2      = (BP + AQ)P + (BQ + AQ + AP)Q
;         = (BPP + AQP) + (BQQ + AQQ + APQ)
;         = BPP + AQP + BQQ + AQQ + APQ
;         = (BPP + BQQ) + (AQP + AQQ + APQ)
;         = B(PP + QQ) + A(QP + QQ + PQ)
;         = B(P^2 + Q^2) + A(Q^2 + 2PQ)
;
;
;         So P' is P^2 + Q^2 and Q' is Q^2 + 2PQ
;
; Tp'q':  A <- B(Q^2 + 2PQ) + A(Q^2 + 2PQ) + A(P^2 + Q^2)
;         B <- B(P^2 + Q^2) + A(Q^2 + 2PQ)

(define (iseven n) (= (remainder n 2) 0))

(define (fib-iter a b p q count)
  (cond ((= count 0) b)
        ((iseven count)
         (fib-iter a
                   b
                   (+ (* p p) (* q q))
                   (+ (* q q) (* 2 (* p q)))
                   (/ count 2)
         )
        )
        (else (fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b p) (* a q))
                        p
                        q
                        (- count 1)
              )
        )
  )
)
(define (fib n)
  (fib-iter 1 0 0 1 n)
)

(fib 50)
