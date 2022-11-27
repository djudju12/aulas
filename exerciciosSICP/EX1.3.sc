(define (square a) (* a a))
(define (sum-square a b) (+ (square a) (square b) ))
(define (maior a b) (if (> b a) b a))

(define (squareMaior a b c)
    (cond ((or (and (> b a) (> a c)) (and (> a c) (> b c))) (sum-square b a))
          ((or (and (> c a) (> a b)) (and (> a c) (> c b))) (sum-square c a))
          (else (sum-square b c))))


(display(squareMaior  1 2 3))