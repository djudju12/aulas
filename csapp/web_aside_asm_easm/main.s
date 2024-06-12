	.file	"main.c"
	.text
	.globl	tmult_ok_asm
	.type	tmult_ok_asm, @function
tmult_ok_asm:
.LFB23:
	.cfi_startproc
	endbr64
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
	testq	%rdi, %rdi
	setg	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	tmult_ok_asm, .-tmult_ok_asm
	.globl	umult_ok_asm
	.type	umult_ok_asm, @function
umult_ok_asm:
.LFB24:
	.cfi_startproc
	endbr64
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
	testq	%rdi, %rdi
	setne	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	umult_ok_asm, .-umult_ok_asm
	.globl	tmult_ok2
	.type	tmult_ok2, @function
tmult_ok2:
.LFB25:
	.cfi_startproc
	endbr64
#APP
# 27 "main.c" 1
	imulq %rsi,%rdi
	movq %rdi,(%rdx)
	setae %dil

# 0 "" 2
#NO_APP
	movzbl	%dil, %eax
	ret
	.cfi_endproc
.LFE25:
	.size	tmult_ok2, .-tmult_ok2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	endbr64
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdx
	movl	$100, %esi
	movl	$100, %edi
	call	tmult_ok2
	movl	%eax, %ecx
	movq	(%rsp), %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L7
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE26:
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
