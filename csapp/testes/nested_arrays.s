	.file	"nested_arrays.c"
	.text
	.p2align 4
	.globl	fix_set_diag
	.type	fix_set_diag, @function
fix_set_diag:
.LFB23:
	.cfi_startproc
	endbr64
	leaq	4198400(%rdi), %rax
	.p2align 4,,10
	.p2align 3
.L2:
	movl	%esi, (%rdi)
	addq	$4100, %rdi
	cmpq	%rax, %rdi
	jne	.L2
	ret
	.cfi_endproc
.LFE23:
	.size	fix_set_diag, .-fix_set_diag
	.p2align 4
	.globl	fix_set_diag_opt
	.type	fix_set_diag_opt, @function
fix_set_diag_opt:
.LFB24:
	.cfi_startproc
	endbr64
	leaq	4198400(%rdi), %rax
	.p2align 4,,10
	.p2align 3
.L6:
	movl	%esi, (%rdi)
	addq	$4100, %rdi
	cmpq	%rdi, %rax
	jne	.L6
	ret
	.cfi_endproc
.LFE24:
	.size	fix_set_diag_opt, .-fix_set_diag_opt
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%01d "
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	leaq	-4194304(%rsp), %r11
	.cfi_def_cfa 11, 4194344
.LPSRL0:
	subq	$4096, %rsp
	orq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LPSRL0
	.cfi_def_cfa_register 7
	subq	$24, %rsp
	.cfi_def_cfa_offset 4194368
	movl	$4194304, %edx
	xorl	%esi, %esi
	movq	%fs:40, %rax
	movq	%rax, 4194312(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rcx
	leaq	4198400(%rsp), %r13
	movq	%rcx, %rdi
	call	memset@PLT
	.p2align 4,,10
	.p2align 3
.L9:
	movl	$3, (%rax)
	addq	$4100, %rax
	cmpq	%r13, %rax
	jne	.L9
	leaq	4096(%rsp), %rbp
	leaq	.LC0(%rip), %r12
.L10:
	leaq	-4096(%rbp), %rbx
	.p2align 4,,10
	.p2align 3
.L11:
	movl	(%rbx), %edx
	movq	%r12, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$4, %rbx
	call	__printf_chk@PLT
	cmpq	%rbp, %rbx
	jne	.L11
	movl	$10, %edi
	leaq	4096(%rbx), %rbp
	call	putchar@PLT
	cmpq	%r13, %rbp
	jne	.L10
	movq	4194312(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L17
	addq	$4194328, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L17:
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
