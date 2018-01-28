(define (enumerate-interval low high)
  (if (> low high)
    '()
    (cons low (enumerate-interval (+ low 1) high))))

(define (flatmap proc seq)
  (fold-left append '() (map proc seq)))

(define (unique-triples n)
  (flatmap (lambda (i)
             (flatmap (lambda (j) 
                        (map (lambda (k) (list i j k)) 
                             (enumerate-interval 1 (- j 1))))
                      (enumerate-interval 1 (- i 1))))
                  (enumerate-interval 1 n)))

(unique-triples 5)

(define (sum-equals? seq n)
  (= n (fold-left + 0 seq)))

(sum-equals? (list 1 2 3) 6)

(define (append-sum seq)
  (append seq (list (fold-left + 0 seq))))

(append-sum (list 1 2 3))

(define (all-ordered-triples-sum-lte n s)
  (map append-sum (filter (lambda (seq) (sum-equals? seq s)) (unique-triples n))))

(all-ordered-triples-sum-lte 5 10)
(all-ordered-triples-sum-lte 10 5)
(all-ordered-triples-sum-lte 10 6)
(all-ordered-triples-sum-lte 12 12)
