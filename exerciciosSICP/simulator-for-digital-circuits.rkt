#lang sicp
; (get-signal <wire> )
; returns the current value of the signal on the wire

; (set-signal! <wire> <new value>)
; changes the value of the signal on the wire to the new value 

; (add-action! <wire> <procedure of no arguments>)
; asserts that the designated procedure should be run whenever
; the signal on the wire changes value. Such procedures are the 
; vehicles by which changes in the signal value on the wire are 
; communicated to other wires. 

(define (inverter input output)
   (define (inverter-input)
      (let ((new-value (logical-not (get-signal input))))
         (after-delay inverter-delay
                      (lambda () set-signal! output new-value))))
   (add-action! input inverter-input) 'ok)

((define (logical-not s)
   (cond ((= s 0) 1)
         ((= s 1) 0)
         (else (error "Invalid Signal" s)))))

(define (and-gate a1 a2 out-put)
   (define (and-action-procedure)
      (let ((new-value 
               (logical-and (get-signal a1) (get-signal a2))))
            (after-delay
               and-gate-delay
               (lambda () (set-signal! output new-value)))))
   (add-action! a1 and-action-procedure)
   (add-action! a2 and-action-procedure)
   'ok)

(define (logical-and s1 s2)
   (cond ((and (= s1 1) (= s2 1)) 1)
         (else 0)))

(define (or-gate a1 a2 out-put)
   (define (or-action-procedure)
      (let ((new-value 
               (logical-or (get-signal a1) (get-signal a2))))
            (after-delay
               or-gate-delay
               (lambda () (set-signal! output new-value)))))
   (add-action! a1 or-action-procedure)
   (add-action! a2 or-action-procedure)
   'ok)

(define (logical-or s1 s2)
   (cond ((= s1 1) 1)
         ((= s2 1) 1)
         (else 0)))


; (define (or-gate s1 s2)
;    (define (or-action-procedure)
;       (let ((new-value 
;                (logical-and (logical-not (get-signal s1)) (logical-not (get-signal s2)))))
;             (after-delay
;                (+ and-gate-delay (* logical-not 3))
;                (lambda () (set-signal! output new-value)))))
;    (add-action! a1 or-action-procedure)
;    (add-action! a2 or-action-procedure)
;    'ok)

(define (half-adder a b s c )
   (let ((d (make-wire)) (e (make-wire)))
      (or-gate a b d)
      (and-gate a b c)
      (inverter c e)
      (and-gate d e s)
      'ok))


(define (full-adder a b c-in sum c-out)
   (let ((s (make-wire)) (c1 (make-wire)) (c2 (make-wire)))
      (half-adder b c-in s c1)
      (half-adder a s sum c2)
      (or-gate c1 c2 c-out)
      'ok))

;https://www.inchmeal.io/sicp/ch-3/ex-3.30.html
(define (ripple-carry-adder As Bs sum C)
   (let ((carry (make-wire)) 
      (if (null? As) 
            (set-signal! C 0)
         (begin 
            (ripple-carry-adder (cdr As) (cdr Bs) (cdr sum) carry)
            (full-adder (car As) (car Bs) (car sum) C))))))

(define (make-wire)
   (let ((signal-value 0) (action-procedures '()))
      (define (set-my-signal! new-value)
         (if (not (= signal-value new-value))
             (begin (set! signal-value new-value)
                    (call-each action-procedures))
               'done))
               
   (define (accept-action-procedure! proc)
      (set! action-procedures (cons proc action-procedures))
      (proc))
   
   (define (dispatch m)
      (cond ((eq? m 'get-signal) signal-value)
            ((eq? m 'set-signal) set-my-signal!)
            ((eq? m 'add-action) accept-action-procedure!)
            (else (error "Unknow op -- WIRE" m))))
   
   dispatch))

(define (call-each procedures)
   (if (null? procedures)
       'done
       (begin
           ((car procedures))
           (call-each (cdr procedures)))))

(define (get-signal wire)
   (wire 'get-signal))

(define (set-signal! wire new-value)
   ((wire 'get-signal) new-value))

(define (add-action! wire action-procedure)
   ((wire 'add-action) action-procedure))
    

