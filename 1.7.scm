(define (sqrt-iter guess x)
  (if (good-enough guess x)
    guess
    (sqrt-iter (improve guess x) x)
	)
)

(define (improve guess x)
	(average guess (/ x guess))
)

(define (average x y)
	(/ 	(+ x y)
		 	2)
)

(define (sqrt x)
	(sqrt-iter 1.0 x)
)

; The book implementation of good-enough
(define (good-enough guess x)
	(< (abs (- (square guess) x)) 0.001)
)

; The test isn't very effective for small numbers because 0.001 isn't a very significant threshold to test if the guess is good enough, the estimation
; of the square root gets more efficient as the number grows larger because the 0.001 will pose less and less of a relative difference.
(sqrt 0.0009)	; 0.03      procedure returns .04030062264654547
(sqrt 9) 			; 3         procedure returns 3.00009155413138
(sqrt 900000) ; 948.683.. procedure returns 948.6832980505158

;The alternative implementation of good-enough where the difference of guess from one iteration to the next is compared based on a fraction of the guess.
(define (good-enough guess x)
	(< 	(abs (- (improve guess x) guess)) 
			(* 0.001 guess)
	)
)

; The test is more effective for small numbers but for large numbers it is less accurate. This is because as the numbers grow the absolute value of 0.001
; will be less than whatever 0.001 * guess is. So as long as the guess is larger than 1, this good-enough test will be less accurate than the previous one. 
(sqrt 0.0009)	; 0.03      procedure returns .03002766742182557
(sqrt 9) 			; 3         procedure returns 3.00009155413138
(sqrt 900000) ; 948.683.. procedure returns 949.0206159647947
