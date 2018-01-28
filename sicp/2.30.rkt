#lang racket
; scale-tree without higher-order procedures
(define scale-tree
  (λ (tree factor)
     (cond ((null? tree) '())
	   ((not (pair? tree)) (* tree factor))
	   (else (cons (scale-tree (car tree) factor)
		       (scale-tree (cdr tree) factor))))))

(scale-tree (list 1 (list 2 (list 3 4) 5) (list 6 7)) 10)

; scale-tree with map and recursion
(define (scale-tree tree factor)
  (map (λ (sub-tree)
	  (if (pair? sub-tree)
	    (scale-tree sub-tree factor)
	    (* sub-tree factor)))
       tree))

; square tree without higher-order procedures
(define square-tree
  (λ (tree)
     (cond ((null? tree) '())
	   ((not (pair? tree)) (* tree tree))
	   (else (cons (square-tree (car tree))
		       (square-tree (cdr tree)))))))

(square-tree (list 1 (list 2 (list 3 4) 5) (list 6 7)))

; square-tree with map and recursion
(define (square-tree tree)
  (map (λ (sub-tree)
	  (if (pair? sub-tree)
	    (square-tree sub-tree)
	    (* sub-tree sub-tree)))
       tree))

(square-tree (list 1 (list 2 (list 3 4) 5) (list 6 7)))
