#lang sicp 

; Necessario uma double linked list que fala??
; Proximo, anterior e valor 

;--Node funcs---------------------------
(define (make-node value)
   (cons (list '() '()) 
          value))

(define (prev-node node) (caar node))

(define (set-prev-node! node prev-node)
   (set-car! (car node) prev-node ))

(define (set-next-node! node next-node)
   (set-cdr! (car node) next-node))

(define (next-node node) (cdar node))

(define (value-node node) (cdr node))
;---------------------------------------

(define (make-queue) (cons '() '()))

(define (front-ptr queue) (car queue))

(define (rear-ptr queue) (cdr queue))

(define (set-front-ptr! queue item)
   (set-car! queue item))

(define (set-rear-ptr! queue item)
   (set-cdr! queue item))

(define (empty-queue? queue)
   (null? (front-ptr queue)))

(define (insert-front-queue! queue item)
   (let ((new-node (make-node item)))
      (cond ((empty-queue? queue) 
             (set-front-ptr! queue new-node)
             (set-rear-ptr! queue new-node)
             queue)
             (else 
               (set-next-node! new-node (front-ptr queue))
               (set-prev-node! (front-ptr queue) new-node)
               (set-front-ptr! queue new-node)
               queue))))

(define (insert-rear-queue! queue item)
   (let ((new-node (make-node item)))
      (cond ((empty-queue? queue) 
             (set-front-ptr! queue new-node)
             (set-rear-ptr! queue new-node)
             queue)
             (else 
               (set-prev-node! new-node (rear-ptr queue))
               (set-next-node! (rear-ptr queue) new-node)
               (set-rear-ptr! queue new-node)
               queue))))

(define (delete-rear-queue! queue)
   (cond ((empty-queue? queue)
          (error "DELETE called with an empty queue" queue))
         (else
            (set-next-node! (prev-node (rear-ptr queue)) (make-node '()))
            (set-rear-ptr! queue (prev-node (rear-ptr queue))))))

(define (delete-front-queue! queue)
   (cond ((empty-queue? queue)
          (error "DELETE called with an empty queue" queue))
         (else
            (set-prev-node! (next-node (front-ptr queue)) (make-node '()))
            (set-front-ptr! queue (next-node (front-ptr queue))))))

(define (print-queue queue) 
   (display "[ ")
   (define (print current-node)
      (cond ((null? (value-node current-node)) (display "]"))
             (else 
               (display (value-node current-node))
               (display " ")
               (print (next-node current-node))) ))
   (print (front-ptr queue)))

(define q1 (make-queue))
(insert-front-queue! q1 'a)
(insert-rear-queue! q1 'b)
(insert-front-queue! q1 'g)
(insert-front-queue! q1 'c)
(insert-rear-queue! q1 'f)
; q1
(newline)
; (display (value-node (next-node (next-node (front-ptr q1)))))
(print-queue q1)
(delete-rear-queue! q1)
(newline)
(print-queue q1)
(delete-front-queue! q1)
(newline)
(print-queue q1)
(delete-front-queue! q1)
(delete-front-queue! q1)
(delete-front-queue! q1)

(newline)
(print-queue q1)
; q1

; Quando temos um pair 
;    OO-> Next
;    |
;    *
;    value

; agora teremos 
;        value
;          |
;  prev <-OOO-> next
