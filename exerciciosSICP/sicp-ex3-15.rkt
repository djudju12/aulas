#lang sicp

(define x (list 'a 'b))
(define z1 (cons x x))
;          a          b
;          ^          ^
;          |          |
; x ----> [o][o] --> [o][^]
;          ^  ^   
;          |  | 
; z1 ---> [o][o]

(define z2 (cons (list 'a 'b) (list 'a 'b)))
; z2 -.--> [o][o] --> [o][^] 
;     |     |          |
;     |     a          b
;     |     |          | 
;     .--> [o][o] --> [o][^] 

(define (set-to-wow! x) (set-car! (car x) 'wow) x)

(set-to-wow! z1)
;         wow         b
;          ^          ^
;          |          |
; x ----> [o][o] --> [o][^]
;          ^  ^   
;          |  | 
; z1 ---> [o][o]

(set-to-wow! z2)
;                     a
;                     ^
;                     |
; z2 ---> [o][o] --> [o][o] --> [o][^] 
;          |                     |
;          |                     *
;          |         wow         b
;          |          ^          *
;          |          |          | 
;          .-------> [o][o] --> [o][^] 