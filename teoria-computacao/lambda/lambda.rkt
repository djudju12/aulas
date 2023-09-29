#lang scheme

; tipo de dados básicos utilizando calculo lambda

; booleano de church verdadeiro = Λx.Λy.x verdadeiro = Λx.Λy.y
(define verdadeiro (lambda (x) (lambda (y) x)))
(define falso (lambda (x) (lambda (y) y)))
(define negar (lambda (p) ((p falso) verdadeiro)))

; se p = falso entao falso senao q
(define se (lambda (p) (lambda (q) ((p q) falso))))

(       ((se verdadeiro) verdadeiro))
(negar falso)
