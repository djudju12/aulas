	.file	"incr.c"
	.text
	.globl	bad_incr
	.type	bad_incr, @function
bad_incr:
.LFB23:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	addl	$1, %eax
	movl	%eax, (%rdi)
	ret
	.cfi_endproc
.LFE23:
	.size	bad_incr, .-bad_incr
	.globl	lock_incr
	.type	lock_incr, @function
lock_incr:
.LFB24:
	.cfi_startproc
	endbr64
#APP
# 8 "incr.c" 1
	lock
	addl $1,(%rdi)
	
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE24:
	.size	lock_incr, .-lock_incr
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movl	$0, (%rsp)
	movl	$0, 4(%rsp)
	movl	$0, %ebx
	jmp	.L4
.L5:
	movq	%rsp, %rdi
	call	lock_incr
	leaq	4(%rsp), %rdi
	call	bad_incr
	addl	$1, %ebx
.L4:
	cmpl	$9, %ebx
	jle	.L5
	movl	4(%rsp), %ecx
	movl	(%rsp), %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L8
	movl	$0, %eax
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
