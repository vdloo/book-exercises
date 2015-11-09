(define (subsets s)
  (if (null? s)
    (list '())
    (let 
      ((rest (subsets (cdr s))))
      (append rest (map 
                     (lambda (item) 
                       (cons (car s) item)) rest)))))

(subsets (list 1 2 3))
; by using (lambda (item) (cons (car s) item)) we make sure that every permuation of each iteration is appended to the list. the procedure takes the first item of the list and passes the rest of the list to the next iteration, but for the current iteration each item in the list needs to be combined with the first item of the original list.
