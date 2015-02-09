(define (cons x y)
  (lambda (m) (m x y)))

; (cons 1 2)
; (lambda (m) (m x y))
; (lambda (m) (m 1 2))

; (define examplecons (cons 1 2))

(define (car z)
  (z (lambda (p q) p)))
; (car examplecons)
; (z (lambda (p q) p))
; (examplecons (lambda (p q) p))
; (lambda (p q) p)
; (lambda (1 2) 1)
; 1

(define (cdr z)
  (z (lambda (p q) q)))
; (car examplecons)
; (z (lambda (p q) p))
; (examplecons (lambda (p q) q))
; (lambda (p q) q)
; (lambda (1 2) 2)
; 2
