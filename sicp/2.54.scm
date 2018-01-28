; exercise 2.54
; define equal? recursively in terms of the basic eq? equality of
; symbols by saying that a and b are equal? if they are both symbols 
; and the symbols are eq?, or if they are both lists such that (car a) 
; is equal? to (car b) and (cdr a) is equal? to (cdr b)

(eq? '(this is a list) '(this is a list))
; #f
(eq? '(this is a list) '(this (is a) list))
; #f

(define (equal? a b)
  (cond ((and (null? a) (null? b)) #t)
        ((or (null? a) (null? b)) #f)
        ((and (pair? a) (pair? b)) 
           (and 
             (equal? (car a) (car b)) 
             (equal? (cdr a) (cdr b))))
        ((or (pair? a) (pair? b)) #f)
        (else (eq? a b))))


(equal? '(this is a list) '(this is a list))
; #t
(equal? '(this is a list) '(this (is a) list))
; #f

