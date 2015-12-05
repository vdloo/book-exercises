(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (accumulate-n op init seqs)
  (if (null? (car seqs))
    '()
    (cons (accumulate op init (map car seqs))
          (accumulate-n op init (map cdr seqs)))))

(define (dot-product v w)
  (accumulate + 0 (map * v w)))

(define matrix1 (list (list 8 5) (list 6 1) (list 9 4)))
(define vector1 (list 3 7))

(define (matrix-*-vector m v)
  (map (lambda (row) (dot-product row v)) m))

(matrix-*-vector matrix1 vector1)

(define matrix2 (list (list 2 7 1) (list 8 6 4)))

(define (transpose m)
  (accumulate-n cons '() m))

(transpose matrix2)

(define matrix3 (list (list 2 8 1) (list 3 6 4)))
(define matrix4 (list (list 1 7) (list 9 -2) (list 6 3)))

(define (matrix-*-matrix m n)
  (let ((cols (transpose n)))
    (map (lambda (row) (matrix-*-vector cols row)) m)))

(matrix-*-matrix matrix3 matrix4)
