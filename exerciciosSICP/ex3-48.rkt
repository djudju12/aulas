(define (serialized-exchange acc1 acc2)
   (define (sort-accounts)
      (if (< (get-num acc1) (get-num acc2)) 
            (cons acc1 acc2)) 
         (cons acc2 acc1))
   (let ((accs (sort-accounts)))
      (let ((serializer1 ((car accs) 'seralizer))
            (serializer2 ((cdr accs) 'seralizer)))
         ((serliazer1 (serializer2 exchange))
            account1
            account2))))

(define (exchange acc1 acc2)
   (let ((difference (- (acc1 'balance)
                        (acc2 'balance))))
      ((acc1 'withdraw) difference)
      ((acc2 'deposit) difference)))
      