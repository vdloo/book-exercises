(define (make-rat n d)
  (let ((g (gcd n d)))
    (if (> d 0)
      (cons (/ n g) (/ d g))
      (cons (* -1 (/ n g)) (* -1 (/ d g))))))

(define (numer x) (car x))
(define (denom x) (cdr x))

(define (print-rat x)
 (newline)
 (display (numer x))
 (display "/")
 (display (denom x)))

(print-rat (make-rat 1 2))
(print-rat (make-rat 1 -2))
(print-rat (make-rat -1 -2))
(print-rat (make-rat -1 2))
