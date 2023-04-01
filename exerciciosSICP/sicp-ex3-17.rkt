#lang sicp 

(define (last-pair x) 
   (if (null? (cdr x)) x (last-pair (cdr x))))

(define (append! lista elemento)
   (if (pair? lista)
      (set-cdr! (last-pair lista) (list elemento))
         (set! lista elemento)))

(define (count-pairs x)
   (define pairs (list '()))
   (define ret 0)
   (define (count x)
      (if (and (pair? x) (not (memq x pairs)))
            (begin (set! pairs (cons x pairs))
                   (set! ret (+ ret 1))
                   (count (car x))
                   (count (cdr x)))))
   (count x) ret)
   

(define l1 (cons 1 (cons 2 (cons 3 '()))))

(define x1 (cons '() '()))
(define y1 (cons x1 x1))
(define l2 (cons y1 '()))

(define x2 (cons 1 (cons 2 '())))
(define l3 (cons x2 x2))

(define x3  (cons '() '()))
(define y3  (cons x3 x3))
(define l4 (cons y3 y3))

(count-pairs l1)
(count-pairs l2)
(count-pairs l3)
(count-pairs l4)
(define a (list 'a 'b 'c))
(count-pairs a) ; 3

(set-car! a (cddr a)) 
(count-pairs a) ; 4 

(set-car! a (cdr a) )
(set-car! (cdr a) (cddr a) ) ; 7

(count-pairs a)
