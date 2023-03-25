#lang sicp

(define (mystery x)
   (define (loop x y)
      (if (null? x)
      y
      (let ((temp (cdr x)))
         (set-cdr! x y)
         (loop temp x))))
   (loop x '()))

(define v (list 'a 'b 'c 'd ))
(define w (mystery v))

(display w)
(display v)
(newline)

; mystery reverte a lista, pegando sempre o primeiro elemendo e cdrzando em uma nova lista, que seria a lista y
;
;      a         b         c         d
;      ^         ^         ^         ^   
;      |         |         |         |   
;v -> [o][o] -> [o][o] -> [o][o] -> [o][^]    
;  
; After evaluation:
;
;v ----.  Pq o unico set-cdr! usado em V é na primeira iteração, depois é usado nos temps
;       \-------------------------.   
;                                 |
;      d         c         b      |    a
;      ^         ^         ^      |    ^   
;      |         |         |      |    |   
;w -> [o][o] -> [o][o] -> [o][o] -*-> [o][^]    

;É possivel provar o que esta acima da seguinte forma:

(set-car! v 'f)
(newline)
(display w)
(display v)
