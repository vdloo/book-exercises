(define (foldr op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (foldl op init seqs)
  (define (iter result rest)
    (if (null? rest)
      result
      (iter (op result (car rest))
            (cdr rest))))
  (iter init seqs))

(foldr / 1 (list 1 2 3))      ; 3/2
(foldl / 1 (list 1 2 3))      ; 1/6
(foldr list '() (list 1 2 3)) ; (1 (2 (3 ())))
(foldl list '() (list 1 2 3)) ; (((() 1) 2) 3)

; the porperty that op should satisfy to guarantee that fold-right and fold-left will product the same values for any sequence is commutativity.
