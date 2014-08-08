(define (gcd a b)
  (if (= b 0)
    a
    (gcd b (remainder a b))
  )
)

; Normal order evaluation
;
;  (if (= 40 0)
;    206
;    (gcd 40 (remainder 206 40))
;  )
;
;  (if (= (remainder 206 40) 0)
;    40
;    (gcd (remainder 206 40) (remainder 40 (remainder 206 40)))
;  )
;
;  (if (= 6 0)  ; 1
;    40
;    (gcd (remainder 206 40) (remainder 40 (remainder 206 40)))
;  )
;
;  (gcd (remainder 206 40) (remainder 40 (remainder 206 40)))
;
;  (if (= (remainder 40 (remainder 206 40)) 0)
;    (remainder 206 40)
;    (gcd (remainder 40 (remainder 206 40)) (remainder (remainder 206 40) (remainder 40 (remainder 206 40))))
;  )
;
;  (if (= (remainder 40 6) 0) ; 2
;    (remainder 206 40)
;    (gcd (remainder 40 (remainder 206 40)) (remainder (remainder 206 40) (remainder 40 (remainder 206 40))))
;  )
;
;  (if (= 4 0) ; 3
;    (remainder 206 40)
;    (gcd (remainder 40 (remainder 206 40)) (remainder (remainder 206 40) (remainder 40 (remainder 206 40))))
;  )
;
;  (gcd (remainder 40 (remainder 206 40)) (remainder (remainder 206 40) (remainder 40 (remainder 206 40))))
;
;  (if (= ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) 0)
;    (remainder 40 (remainder 206 40))
;    (gcd ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))))
;  )
;    
;  (if (= ((remainder (remainder 206 40) (remainder 40 6))) 0) ; 4
;    (remainder 40 (remainder 206 40))
;    (gcd ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))))
;  )
;    
;  (if (= ((remainder (remainder 206 40) 4)) 0) ; 5
;    (remainder 40 (remainder 206 40))
;    (gcd ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))))
;  )
;
;  (if (= ((remainder 6 4)) 0) ; 6
;    (remainder 40 (remainder 206 40))
;    (gcd ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))))
;  )
;
;  (if (= 2 0) ; 7
;    (remainder 40 (remainder 206 40))
;    (gcd ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))))
;  )
;
;  (gcd ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))))
;
;  (if (= (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) 0)
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 6)))) 0) ; 8
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) 4))) 0) ; 9
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= (remainder (remainder 40 (remainder 206 40)) ((remainder 6 4))) 0) ; 10
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= (remainder (remainder 40 (remainder 206 40)) (2)) 0) ; 11
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= (remainder (remainder 40 6) (2)) 0) ; 12
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= (remainder 4 (2)) 0) ; 13
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (if (= 0 0) ; 14
;    (remainder (remainder 206 40) (remainder 40 (remainder 206 40)))
;    (gcd (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40))))) (remainder (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) (remainder (remainder 40 (remainder 206 40)) ((remainder (remainder 206 40) (remainder 40 (remainder 206 40)))))))
;  )
;
;  (remainder (remainder 206 40) (remainder 40 (remainder 206 40))) 
;  (remainder (remainder 206 40) (remainder 40 6)) ; 15
;  (remainder (remainder 206 40) 4) ; 16
;  (remainder 6 4) ; 17
;  2 ; 18
; 
; The remainder operation is evaluated 18 times in normal-order evaluation
;
; Applicative order evaluation
;
;  (if (= 40 0)
;    206
;    (gcd 40 (remainder 206 40))
;  )
;
;  (gcd 40 6) ; 1
;
;  (if (= 6 0)
;    40
;    (gcd 6 (remainder 40 6))
;  )
;
;  (gcd 6 4) ; 2
;
;  (if (= 4 0)
;    6
;    (gcd 4 (remainder 6 4))
;  )
;
;  (gcd 4 2) ; 3
;
;  (if (= 2 0)
;    4
;    (gcd 2 (remainder 4 2))
;  )
;
;  (gcd 2 0) ; 4
;
;  (if (= 0 0)
;    2
;    (gcd 0 (remainder 2 0))
;  )
;
;  2
;
;  The remainder operation is evaluated 4 times in applicative-order evaluation
