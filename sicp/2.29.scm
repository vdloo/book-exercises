(define make-mobile
  (lambda (left right)
    (list left right)))

(define make-branch
  (lambda (length structure)
    (list length structure)))

; a
(define left-branch
  (lambda (mobile)
    (car mobile)))

(define right-branch
  (lambda (mobile)
    (cadr mobile)))

(define branch-length
  (lambda (branch)
    (car branch)))

(define branch-structure
  (lambda (branch)
    (cadr branch)))

; b
(define branch-weight
  (lambda (branch)
    (if (pair? (branch-structure branch))
      (total-weight (branch-weight brach))
      (branch-structure branch))))

(define total-weight
  (lambda (mobile)
    (apply + (map branch-weight
        (map (lambda (proc) (proc mobile)) 
             (list left-branch right-branch))))))

(define l (make-branch 5 7))
(define r (make-branch 10 14))
(define mobile (make-mobile l r))
(total-weight mobile)

; c

(define branch-torque
  (lambda (branch)
    (* (branch-length branch) (branch-weight branch))))

(define branch-balanced?
  (lambda (branch)
    (if (pair? (branch-structure branch))
      (mobile-balanced? branch)
      #t)))

(define mobile-balanced?
  (lambda (branch)
    (and (= 
           (branch-torque (left-branch branch)) 
           (branch-torque (right-branch branch))) 
         (branch-balanced? (left-branch branch)) 
         (branch-balanced? (right-branch branch)))))

(define l (make-branch 5 10))
(define r (make-branch 5 10))
(define balanced-mobile (make-mobile l r))

(mobile-balanced? balanced-mobile) ; #t

(define l (make-branch 6 10))
(define r (make-branch 5 10))
(define unbalanced-mobile (make-mobile l r))

(mobile-balanced? unbalanced-mobile) ; #f

; d
;(define (make-mobile left right)
;  (cons left right))

;(define (make-branch length structure)
;  (cons length-structure))

; only right-branch and branch-structure would be affected, those cadrs would become cdrs
