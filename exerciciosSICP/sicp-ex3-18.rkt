#lang sicp

; Não funciona se o primeiro elemento da lista faz parte do ciclo
; (define (cycle? list)
;    (define (is-cycle? sub-list)
;       (cond ((null? (cdr sub-list)) "is not a cycle")
;             ((equal? (cdr sub-list) list) "is cycle")
;             (else (is-cycle? (cdr sub-list)))))
;    (is-cycle? list))


(define (cycle? list)
   (define (safe-cdr x)
      (if (pair? x) 
         (cdr x)
         '()))

   (define (iter tortoise hare)
      (cond ((not (pair? tortoise)) #f)
            ((not (pair? hare)) #f)
            ((equal? tortoise hare) #t)
            ((equal? tortoise (safe-cdr hare)) #t)
            (else (iter (safe-cdr tortoise) (safe-cdr (safe-cdr hare))))))

   (iter (safe-cdr list) (safe-cdr (safe-cdr list))))


(define (make-cycle x)
   (set-cdr! (last-pair x) x)
   x)

(define (last-pair x)
   (if (null? (cdr x))
      x
      (last-pair (cdr x))))

(define z (make-cycle (list 'a 'b 'c 'd 'f)))
(define f (list 'a 'b 'c 'd 'f))

; (display (cycle? z))
; (display (cycle? f))
(cycle? (make-cycle '(1 2 3 4 5 6 7 8 9 10))) ; -> #t   
(cycle? (append '(1 2 3 4 5) (make-cycle '(6 7 8 9 10 11)))) ; -> #t 
