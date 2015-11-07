(define (reverse l)
  (define (prepend l1 l2)
    (cons (car l1) l2))
  (define (reverse-iter l1 l2)
    (if (null? (cdr l1))
      (prepend l1 l2)
      (reverse-iter (cdr l1) (prepend l1 l2))))
    (reverse-iter l '()))

(define (deep-reverse m)
  (define (prepend l1 l2)
    (cons (car l1) l2))
  (define (reverse-iter l1 l2)
    (if (null? (cdr l1))
      (prepend l1 l2)
      (reverse-iter (cdr (map deep-reverse l1)) (prepend l1 l2))))
  (if (list? m) (reverse-iter m '()) m))

(define x (list (list 1 2 ) (list 3 4)))

x
(reverse x)
(deep-reverse x)
