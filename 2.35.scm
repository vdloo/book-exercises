(define tree (list 1 2 (list 3 4 5 (list 6 7) 8 ) 9))

(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        (else (+ (count-leaves (car x))
                 (count-leaves (cdr x))))))

(count-leaves tree)

(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (map p sequence)
  (accumulate (lambda (x y) (cons (p x) y)) '() sequence))

(define (flatten tree)
  (cond ((null? tree) '())
        ((not (pair? tree)) (list tree))
        (else (append (flatten (car tree)) (flatten (cdr tree))))))

(define (identity x) x)

(define (count-leaves t)
  (accumulate (lambda (x y) (+ y 1)) 0 (map identity (flatten t))))

(count-leaves tree)
