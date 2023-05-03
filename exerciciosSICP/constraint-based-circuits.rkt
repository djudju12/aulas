#lang sicp

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
                        me))))
   (define (process-forget-value)
      (forget-value! sum me)
      (forget-value! a1 me)
      (forget-value! a2 me)
      ; you have to do \this/ because these values may need to be propagated through the adder
      (process-new-value)) 
   (define (me request)
      (cond ((eq? request 'I-have-a-value) (process-new-value))
            ((eq? request 'I-lost-my-value) (process-forget-value))
            (else (error "unknow request: ADDER" request))))
   (connect a1 me)
   (connect a2 me)
   (connect sum me)
   me)

(define (multiplier m1 m2 product)
   (define (process-new-value)
      (cond ((or (and (has-value? m1) (= (get-value m1) 0))
                 (and (has-value? m2) (= (get-value m2) 0)))
                 (set-value! product 0 me))
            ((and (has-value? m1) (has-value? m2)) 
                 (set-value! product 
                             (* (get-value m1) (get-value m2))
                             me))
            ((and (has-value? product) (has-value? m1))
                  (set-value! m2
                              (/ (get-value product)
                                 (get-value m1))
                              me))
            ((and (has-value? product) (has-value? m2))
                  (set-value! m1
                              (/ (get-value product)
                                 (get-value m2))
                              me))))
   (define (process-forget-value)
      (forget-value! product me)
      (forget-value! product me)
      (forget-value! product me)
      (process-new-value))
   (define (me request)
      (cond ((eq? request 'I-have-a-value)  (process-new-value))
            ((eq? request 'I-lost-my-value) (process-forget-value))
            (else (error "Unknow request: MULTIPLIER" request))))
   (connect m1 me)
   (connect m2 me)
   (connect product me)
   me)

(define (constant value connector)
   (define (me request)
      (error "Unknow request: CONSTANT" constant))
   (connect connector me)
   (set-value! connector value me)
   me)

(define (inform-about-value constraint)
   (constraint 'I-have-a-value))

(define (inform-about-no-value constraint)
   (constraint 'I-lost-my-value))

(define (probe name connector)
   (define (print-probe value) 
      (newline) (display "Probe: ") (display name) 
      (display " = ") (display value) (newline)) 
   (define (process-new-value) 
      (print-probe (get-value connector)))
   (define (process-forget-value) (print-probe "?"))
   (define (me request)
      (cond ((eq? request 'I-have-a-value) (process-new-value)) 
            ((eq? request 'I-lost-my-value) (process-forget-value))
            (else (error "Unknow request: PROBE" request))))
      (connect connector me)
      me) 

(define (make-connector)
   (let ((value #f) (informant #f) (constraints '())) 
      (define (set-my-value newval setter)
         (cond ((not (has-value? me)) 
                (set! value newval)
                (set! informant setter)
                (for-each-except setter
                                 inform-about-value
                                 constraints))
               ((not (= value newval))
                (error "Contradiction" (list value newval)))
                (else 'ignored)))
      (define (forget-my-value retractor)
         (if (eq? retractor informant)
             (begin (set! informant #f)
               (for-each-except retractor
                              inform-about-no-value
                              constraints))
             'ignored))
      (define (connect new-constraint)
         (if (not (memq new-constraint constraints))
             (set! constraints
                  (cons new-constraint constraints)))
         (if (has-value? me)
             (inform-about-value new-constraint))
         'done)
      (define (me request)
         (cond ((eq? request 'has-value?)
                (if informant #t #f)) 
               ((eq? request 'value) value)
               ((eq? request 'set-value!) set-my-value)
               ((eq? request 'forget) forget-my-value)
               ((eq? request 'connect) connect)
               (else (error "Unknow op: CONNECETOR" request))))
      me))

(define (for-each-except exception procedure list)
   (define (loop items)
      (cond ((null? items) 'done)
            ((eq? (car items) exception) (loop (cdr items)))
            (else (procedure (car items))
                  (loop (cdr items)))))
   (loop list))

(define (has-value? connector)
   (connector 'has-value?))

(define (get-value connector)
   (connector 'value))

(define (set-value! connector new-value informant)
   ((connector 'set-value!) new-value informant))

(define (forget-value! connector retractor)
   ((connector 'forget) retractor))

(define (connect connector new-constraint)
   ((connector 'connect) new-constraint))

;________________________________________________________________
; Exercise 3.33: Using primitive multiplier, adder, and 
; constant constraints, define a procedure averager that takes
; three connectors a, b, and c as inputs and establishes the
; constraint that the value of c is the average of the values of
; a and b.
;________________________________________________________________

;how can i define A + B? (define a-plus-b)
; (define a (make-connector))
; (define b (make-connector))
; (define average (make-connector))


; (define (calc-average a b c)
;    (let ((x (make-connector))
;          (y (make-connector)))
;       (multiplier x c y)
;       (adder a b y)
;       (constant 2 x)
;       'ok))

; (probe "B" b)
; (calc-average a b average)
; (set-value! a 100 'user)
; (set-value! average 500 'user)

;________________________________________________________________
; Exercise 3.34: Louis Reasoner wants to build a squarer, a
; constraint device with two terminals such that the value
; of connector b on the second terminal will always be the
; square of the value a on the first terminal. He proposes the
; following simple device made from a multiplier:
;
;     (define (squarer a b)
;        (multiplier a a b))
; 
; There is a serious flaw in this idea. Explain.
;________________________________________________________________

; (define (squarer a b)
;    (multiplier a a b))

; (define a (make-connector))
; (define b (make-connector))


; (probe "A" a)
; (probe "B" b)
; (set-value! a 2 'user)
; (squarer a b)
; (forget-value! a 'user)
; (newline)
; (display "doesnt have sufficient information to calc the value o b")
; ; A * A = 4
; ; A? THERESNT A SQR ROOT 
; (set-value! b 2 'user)

;________________________________________________________________
; Exercise 3.35: Ben Bitdiddle tells Louis that one way to
; avoid the trouble in Exercise 3.34 is to define a squarer
; as a new primitive constraint. Fill in the missing portions
; in Ben’s outline for a procedure to implement such a constraint:

; (define (squarer a b)
;    (define (process-new-value)
;       (if (has-value? b)
;          (if (< (get-value b) 0)
;             (error "square less than 0: SQUARER"
;                   (get-value b))
;             ?alternative1?)
;          ?alternative2?))
;    (define (process-forget-value) ?body1?)
;    (define (me request) ?body2?)
;    ?rest of definition?
;    me)
;________________________________________________________________

;_____Newton Methods cap 1
(define (deriv g)
   (lambda (x) (/ (- (g (+ x dx)) (g x)) dx)))

(define dx 0.00001)

(define (newton-transform g)
   (lambda (x) (- x (/ (g x) ((deriv g) x)))))

(define (newtons-method g guess) 
   (fixed-point (newton-transform g) guess))

(define (fixed-point f first-guess)
   (define (close-enough? v1 v2)
      (< (abs (- v1 v2))
         dx))
   (define (try guess)
      (let ((next (f guess)))
         (if (close-enough? guess next)
            next
            (try next))))
   (try first-guess))

(define (square x) (* x x))

(define (sqrt x)
   (newtons-method
      (lambda (y) (- (square y) x)) 1.0))
;__________________________


; (define (squarer a b)
;    (define (process-new-value)
;       (if (has-value? b)
;          (if (< (get-value b) 0)
           
;             (error "square less than 0: SQUARER"
;                   (get-value b))
           
;             ?alternative1?)

;       (error "doesnt have exponent")))
;    (define (process-forget-value) ?body1?)
;    (define (me request) ?body2?)
;    ?rest of definition?
;    me)
