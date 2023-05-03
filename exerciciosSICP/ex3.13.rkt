#lang sicp 


(define (append x y)
   (if (null? x)
      y
      (cons (car x) (append (cdr x) y))))

(define (append! x y)
   (set-cdr! (last-pair x) y)
   x)

(define (last-pair x)
   (if (null? (cdr x)) x (last-pair (cdr x))))

(define (make-cycle x)
  (set-cdr! (last-pair x) x)
  x)


(define z (make-cycle (list 'a 'b 'c)))

; Circular list
;       a         b         c
;       |         |         |  
; z -> [o][-]--->[o][-]--->[o][o]
;       /\                     | 
;       |                      |
;       |                      | 
;       |______________________|

(last-pair z)