(define empty-board '())

(define (enumerate-interval low high)
  (if (> low high)
    '()
    (cons low (enumerate-interval (+ low 1) high))))

(define (compose-position row column)
  (cons row column))

(define (flatmap proc seq)
  (accumulate append '() (map proc seq)))

(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (foldr op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (append seq1 seq2)
  (accumulate (lambda (x y) (cons x y)) seq2 seq1))

(define (adjoin-position new-row new-column rest-of-queens)
  (append rest-of-queens (list (compose-position new-row new-column))))

(define (columns-apart? queen-a queen-b)
  (- (cdr queen-b) (cdr queen-a)))

(define (verify-no-collision queen-a queen-b)
  (and 
    (not (= (car queen-a) (car queen-b)))
    (not (= (- (car queen-a) (car queen-b)) 
            (columns-apart? queen-a queen-b)))
    (not (= (- (car queen-b) (car queen-a)) 
            (columns-apart? queen-a queen-b)))))

(define (getitem seq n)
  (if (null? seq)
    (raise "StopIteration" #f)
    (if (= 0 n)
      (car seq)
      (getitem (cdr seq) (- n 1)))))

(define (all seq)
  (foldr (lambda (prev next) (and prev next)) #t seq))

(define (safe? next-column positions)
  (all
    (map 
      (lambda 
        (queen-a) 
          (verify-no-collision 
            queen-a 
            (getitem positions (- next-column 1)))) 
      (filter 
        (lambda (position) (not (= next-column (cdr position)))) 
        positions))))

(define (queens board-size)
  (define (queen-cols k) 
    (if (= k 0)
      (list empty-board)
      (filter
        (lambda (positions) (safe? k positions))
        (flatmap
          (lambda (rest-of-queens)
            (map 
              (lambda (new-row)
                (adjoin-position new-row k rest-of-queens))
              (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

(define (get-amount-of-queen-solutions n)
  (length (queens n)))

; 1 0 0 2 10 4 40 92 352 724
(map get-amount-of-queen-solutions (enumerate-interval 1 10))

(queens 8)
