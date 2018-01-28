(define (print-when-evaluated x) 
  (newline)
  (display "Evaluated callback!")
)

; zero is a function that returns (lambda (x) x)
(define zero (lambda (f) (lambda (x) x)))

((zero print-when-evaluated) 0) ; should not print "Evaluated callback!"

(define (add-1 n)
  (lambda (f) (lambda (x) (f ((n f) x)))))

; one is a function that returns (lambda (x) (f (lambda (x) x) x))
(define one (add-1 zero))
((one print-when-evaluated) 0) ; should print "Evaluated callback!" once

(define one (lambda (f) (lambda (x) (f x))))
((one print-when-evaluated) 0) ; should print "Evaluated callback!" once
;one

; two is a function that returns (lambda (x) (f (lambda (x) (f (f x)))))
(define two (add-1 one))
((two print-when-evaluated) 0) ; should print "Evaluated callback!" twice

(define two (lambda (f) (lambda (x) (f (f x)))))
((two print-when-evaluated) 0) ; should print "Evaluated callback!" twice

(define (add-church-numerals a b)
  (lambda (f) (lambda (x) ((a f) ((b f) x)))))

(define three (add-church-numerals one two))
((three print-when-evaluated) 0) ; should print "Evaluated callback!" three times

(define five (add-church-numerals three two))
((five print-when-evaluated) 0) ; should print "Evaluated callback!" five times
