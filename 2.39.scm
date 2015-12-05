(define l1 (list 1 2 3 4 5 6 7 8 9 10))

(define (reverse sequence)
  (fold-right (lambda (x y) (append y (list x))) '() sequence))

(reverse l1)

(define (reverse sequence)
  (fold-left (lambda (x y) (cons y x)) '() sequence))

(reverse l1)
