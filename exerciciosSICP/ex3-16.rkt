#lang sicp

; Exercise 3.16:
; Show that this procedure is not correct. In particular, draw
; box-and-pointer diagrams representing list structures made
; up of exactly three pairs for which Ben’s procedure would
; return 3; return 4; return 7; never return at all.

(define (count-pairs x)
   (if (not (pair? x))
      0
      (+ (count-pairs (car x))
         (count-pairs (cdr x))
         1)))


(define w (list 'a 'b 'c))
(count-pairs w)
(define w ())
;
;
;
;
;
;
