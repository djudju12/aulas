#lang sicp 


; Eval definition 

(define (eval exp env)
   (cond ((self-evaluating? exp) exp)

         ((variable? exp) (lookup-variable-value exp env))
         
         ((quoted? exp) (text-of-quotation exp))

         ((assignment? exp) (eval-assignment exp env))

         ((definition? exp) (eval-definition exp env))

         ((if? exp) (eval-if exp env))

         ((lambda? exp)
          (make-procedure (lambda-parameters exp)
                          (lambda-body exp)
                          env))

         ((begin? exp)
          (eval-sequence (begin-actions exp) env))

         ((cond? exp) (eval (cond->if exp) env))
         
         ((application? exp)
          (my-apply (eval (operator exp) env)
                 (list-of-values (operands exp) env)))
         
         (else (error "Unknown expression type -- EVAL" exp))))


;-4.4-----------------------

; (define (and? exp) 
;    (tagged-list? exp 'and))

; (define (or? exp)
;    (tagged-list? exp 'or))

; (define (exp-clauses exp) 
;    (cdr exp))

; (define (expand-and-clauses clauses) 
;    (if (null? clauses)
;          'false
;          (let ((first (car clauses))
;                (rest (cdr clauses)))
;             (if (null? rest)
;                 first
;                 (make-if first
;                          (expand-and-clauses rest)
;                          'false)))))

; (define (expand-or-clauses clauses) 
;    (if (null? clauses)
;          'false
;          (let ((first (car clauses))
;                (rest (cdr clauses)))
;             (if (null? rest)
;                 first
;                 (make-if first
;                          'true
;                          (expand-or-clauses rest))))))

; (define (and->if exp env)
;    (expand-and-clauses (exp-clauses exp)))

; (define (or->if exp env)
;    (expand-or-clauses (exp-clauses exp)))

;-4.8----------------------

;(for (start range step) 
;  ((display start) (newline)) 

; (define (for? exp) 
;    (tagged-list? exp 'for))

; (let (i 10) 
;    (for (i 0 s1)
;     lambda(i) ((display "Hello World")))




;--------------------------

(define (my-apply procedure arguments)
   (cond ((primitive-procedure? procedure)
          (apply-primitive-procedure procedure arguments))
         ((compound-procedure? procedure)
          (eval-sequence 
            (procedure-body procedure)
            (extend-environment
              (procedure-parameters procedure)
              arguments
              (procedure-environment procedure))))
         (else
            (error
              "Unknown procedure type -- APPLY" procedure))))

; list-of-values definition

(define (list-of-values exps env)
    (if (no-operands? exps)
       '()
       (cons (eval (first-operand exps) env)
             (list-of-values (rest-operands exps) env))))

; 

; conditional definition

(define (true? exp) 
   (not (eq? exp false)))

(define (eval-if exp env)
   (if (true? (eval (if-predicate exp) env))
       (eval (if-consequent exp) env)
       (eval (if-alternative exp) env)))

; eval-sequence definition

(define (eval-sequence exps env) 
   (cond ((last-exp? exps) (eval (first-exp exps) env))
         (else (eval (first-exp exps) env)
               (eval-sequence (rest-exps exps) env))))

; eval-assignment definition
(define (eval-assignment exp env) 
   (set-variable-value! (assignment-variable exp) 
                        (eval (assignment-value exp) env)
                        env)
   'ok)


; eval-definition definition
(define (eval-definition exp env) 
   (define-variable! (definition-variable exp) 
                         (eval (definition-value exp) env)
                          env)
   'ok)

; self-evaluating? definition

(define (self-evaluating? exp) 
   (cond ((number? exp) true)
         ((string? exp) true)
         (else false)))

; variable? definition

(define (variable? exp) 
   (symbol? exp))

; quoted? definition

(define (quoted? exp) 
   (tagged-list? exp 'quote))

; text-of-quotation definition

(define (text-of-quotation exp) 
   (cadr exp))

; tagged-list? definition

(define (tagged-list? exp tag) 
   (if (pair? exp)
       (eq? (car exp) tag)
       false))
      
; assignment? definition

(define (assignment? exp) 
   (tagged-list? exp 'set!))

(define (assignment-variable exp) 
   (cadr exp))

(define (assignment-value exp) 
   (caddr exp))

; definition? definition
(define (definition? exp) 
   (tagged-list? exp 'define))

(define (definition-variable exp) 
   (if (symbol? (cadr exp))
       (cadr exp)
       (caadr exp)))

(define (definition-value exp)
   (if (symbol? (cadr exp))
       (caddr exp)
       (make-lambda (cdadr exp)
                    (cddr exp))))

(define (lambda? exp) 
   (tagged-list? exp 'lambda))

(define (lambda-parameters exp) 
   (cadr exp))

(define (lambda-body exp) 
   (cddr exp))

(define (make-lambda parameters body)
   (cons 'lambda (cons parameters body)))

(define (if? exp) 
   (tagged-list? exp 'if))

(define (if-predicate exp) 
   (cadr exp))

(define (if-consequent exp)
   (caddr exp))

(define (if-alternative exp) 
   (if (not (null? (cdddr exp)))
       (cadddr exp)
       'false))

(define (make-if predicate consequent alternative)
   (list 'if predicate consequent alternative))

(define (begin? exp) 
   (tagged-list? exp 'begin))

(define (begin-actions exp) 
   (cdr exp))

(define (last-exp? seq)
   (null? (cdr seq)))

(define (first-exp seq)
   (car seq))

(define (rest-exps seq)
   (cdr seq))

(define (sequence->exp seq)
   (cond ((null? seq) seq)
         ((last-exp? seq) (first-exp seq))

         (else (make-begin seq))))

(define (make-begin seq)
   (cons 'begin seq))

(define (application? exp) (pair? exp))
(define (operator exp) (car exp))
(define (operands exp) (cdr exp))
(define (no-operands? ops) (null? ops))
(define (first-operand ops) (car ops))
(define (rest-operands ops) (cdr ops))

(define (cond? exp) (tagged-list? exp 'cond))
(define (cond-clauses exp) (cdr exp))
(define (cond-else-clause? clause)
   (eq? (cond-predicate clause) 'else))
(define (cond-predicate clause) (car clause))
(define (cond-actions clause) (cdr clause))
(define (cond->if exp)
   (expand-clauses (cond-clauses exp)))

(define (expand-clauses clauses)
   (if (null? clauses)
       'false
       (let ((first (car clauses))
             (rest (cdr clauses)))
         (if (cond-else-clause? first)
             (if (null? rest)
                 (sequence->exp (cond-actions first))
                 (error "ELSE clause isn't last -- COND->IF"
                        clauses))
             (make-if (cond-predicate first)
                      (sequence->exp (cond-actions first))
                      (expand-clauses rest))))))   

(define (make-procedure parameters body env)
   (list 'procedure parameters body env))

(define (compound-procedure? p)
   (tagged-list? p 'procedure))

(define (procedure-parameters p) (cadr p))

(define (procedure-body p) (caddr p))

(define (procedure-environment p) (cadddr p))

(define (enclosing-environment env) (cdr env))

(define (first-frame env) (car env))

(define the-empty-environment '())

(define (make-frame variables values)
   (cons variables values))

(define (frame-variables frame) (car frame))

(define (frame-values frame) (cdr frame))

(define (add-binding-to-frame! var val frame)
   (set-car! frame (cons var (car frame)))
   (set-cdr! frame (cons val (cdr frame))))

(define (extend-environment vars vals base-env)
   (if (= (length vars) (length vals)) 
       (cons (make-frame vars vals) base-env)
       (if (< (length vars) (length vals))
           (error "Too many arguments supplied" vars vals)
           (error "Too few arguments supplied" vars vals))))

(define (lookup-variable-value var env)
   (define (env-loop env)
      (define (scan vars vals)
         (cond ((null? vars)
                (env-loop (enclosing-environment env)))
               ((eq? var (car vars)) (car vals))
               (else (scan (cdr vars) (cdr vals)))))
         (if (eq? env the-empty-environment)
             (error "Unbound variable" var)
            (let ((frame (first-frame env)))
               (scan (frame-variables frame)
                     (frame-values frame)))))
   (env-loop env))

(define (set-variable-value! var val env)
   (define (env-loop env)
      (define (scan vars vals)
         (cond ((null? vars)
                (env-loop (enclosing-environment env)))
               ((eq? var (car vars))(set-car! vals val))
               (else (scan (cdr vars) (cdr vals)))))
      (if (eq? env the-empty-environment)
          (error "Unbound variable -- SET!" var)
          (let ((frame (first-frame env)))
             (scan (frame-variables frame)
                   (frame-values frame)))))
   (env-loop env))

(define (define-variable! var val env)
   (let ((frame (first-frame env)))
      (define (scan vars vals)
         (cond ((null? vars)
                (add-binding-to-frame! var val frame))
               ((eq? var (car vars))(set-car! vals val))
               (else (scan (cdr vars) (cdr vals)))))
      (scan (frame-variables frame)(frame-values frame))))

(define (primitive-procedure? proc)
   (tagged-list? proc 'primitive))

(define (primitive-implementation proc) 
   (cadr proc))

(define meta-map 
   (lambda (f l) 
      (if (null? l) 
         '() 
         (cons (my-apply f `(,(car l))) (meta-map f (cdr l)))))) 

(define primitive-procedures 
   (list (list 'car car)
         (list 'cdr cdr)
         (list 'cons cons)
         (list 'null? null?)
         (list '+ +)
         (list '- -)
         (list '* *)
         (list '/ /)
         (list '= =)
         (list '< <)
         (list '> >)
         (list 'map meta-map)
         ))

(define (primitive-procedure-names)
   (map car primitive-procedures))

(define (primitive-procedure-objects)
   (map (lambda (proc) (list 'primitive (cadr proc)))
        primitive-procedures))

(define (apply-primitive-procedure proc args)
   (apply
    (primitive-implementation proc) args))

(define (setup-environment)
   (let ((initial-env
          (extend-environment (primitive-procedure-names)
                              (primitive-procedure-objects)
                              the-empty-environment)))
      (define-variable! 'true true initial-env)
      (define-variable! 'false false initial-env)
      initial-env))

(define the-global-environment (setup-environment))

; --- end of interpreter

; --- start of RP


(define input-prompt "RPL-Eval input:")
(define output-prompt " RPL-Eval value:")

(define (driver-loop)
   (prompt-for-input input-prompt)
   (let ((input (read)))
      (let ((output (eval input the-global-environment)))
         (announce-output output-prompt)
         (user-print output)))
   (driver-loop))

(define (prompt-for-input string)
   (newline) (newline) (display string) (newline))

(define (announce-output string)
   (newline) (display string) (newline))

(define (user-print object)
   (if (compound-procedure? object)
       (display (list 'compound-procedure
                      (procedure-parameters object)
                      (procedure-body object)
                      '<procedure-env>))
       (display object)))

(driver-loop)