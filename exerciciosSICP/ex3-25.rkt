#lang sicp

; (define (make-table same-key?)
;    (define (teste-key key)
;       (same-key? key)))

(define (is-valid-key? args keys)
   (cond ((and (null? keys) (null? args)) #t) 
         ((memq (car args) keys)
            (is-valid-key? (cdr args) (delete keys (car args)))) 
         (else #f)))

(define (delete list item )
   (cond ((eq? item (car list)) (cdr list)) 
         (else (cons (car list) (delete (cdr list) item)))))

(is-valid-key? '(a b c) '(a b))
; (define a '(a))
; (define b (delete a 'a))
; b
; (null? b)