(define x (list (list 1 2) (list 3 4)))

(define append
  (lambda (l1 l2)
    (cons (car l1) (if (null? (cdr l1)) l2 (append (cdr l1) l2)))))

(define fringe
  (lambda (l1)
    (if (null? l1) 
      '()
      (if (pair? l1)
        (append (fringe (car l1)) (fringe (cdr l1)))
        (cons l1 '())))))

(fringe x)
(fringe (list x x))
(fringe (list (list x x) x))
