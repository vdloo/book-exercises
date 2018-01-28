(define addfive (lambda (x) (+ x 5)))

(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(map addfive (list 1 2 3 4))

(define (map p sequence)
  (accumulate (lambda (x y) (cons (p x) y)) '() sequence))

(map addfive (list 1 2 3 4))

(define (append seq1 seq2)
  (accumulate (lambda (x y) (cons x y)) seq2 seq1))

(append (list 1 2 3 4) (list 5 6 7 8))

(define (length sequence)
  (accumulate (lambda (x y) (+ y 1)) 0 sequence))

(length (list 1 2 3 4))
