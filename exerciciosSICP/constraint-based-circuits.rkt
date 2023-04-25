#lang sicp

(define (has-value? connector))
(define (get-value connector))
(define (set-value! connector new-value informant))
(define (forget-value! connector retractor))
(define (connect connector new-constraint))

(define (adder a1 a2 sum)
   (define (process-new-value)
      (cond ((and (has-value? a1) (has-value? a2))
             (set-value! sum
                        (+ (get-value a1) (get-value a2))
                        me))
            ((and (has-value? a1) (has-value? sum))
             (set-value! a2
                        (- (get-value sum) (get-value a1))
                        me))
            ((and (has-value? a2) (has-value? sum))
             (set-value! a1
                        (- (get-value sum) (get-value a2))
                        me))