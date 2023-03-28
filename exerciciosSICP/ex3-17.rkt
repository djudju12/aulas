#lang sicp 


(define (append! x z)
   (if (null? x) 
       (set! x z)
       (set-cdr! x z)))

(define (count-pairs x)
   (define pairs (list))
   (define (count x)
      (display pairs)   
      (if (not (pair? x))
         0
            (+ (count-pairs (car x))
               (count-pairs (cdr x))
               (if (memq x pairs) 
                  0
               (begin (append! pairs x) 1)))))
   (count x))

(define a (list 'a 'b 'c))
(count-pairs a) ; 3

(set-car! a (cddr a)) 
(count-pairs a) ; 4 

(set-car! a (cdr a) )
(set-car! (cdr a) (cddr a) ) ; 7

(count-pairs a)