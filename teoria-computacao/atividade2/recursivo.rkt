#lang sicp 

(define (F x);
   (define (G) (if (> x 0) (F (- x 1))))
   (define (H) (+ x x))
   (G);
   (H))

(F 23) ; > 46