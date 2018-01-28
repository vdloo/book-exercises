(define (prepend l1 l2)
  (cons (car l1) l2))

(define (reverse-iter l1 l2)
  (if (null? (cdr l1))
    (prepend l1 l2)
    (reverse-iter (cdr l1) (prepend l1 l2))))

(define (reverse l)
  (reverse-iter l '()))

(reverse (list 23 72 149 34))
