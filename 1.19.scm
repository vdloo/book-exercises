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
;
