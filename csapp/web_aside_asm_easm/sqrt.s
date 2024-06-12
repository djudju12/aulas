	.file	"sqrt.c"
	.text
	.globl	sqrtd
	.type	sqrtd, @function
sqrtd:
.LFB23:
	.cfi_startproc
	endbr64
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
#APP
# 5 "sqrt.c" 1
	sqrtsd %xmm0,%xmm1
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE23:
	.size	sqrtd, .-sqrtd
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"%lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movsd	.LC1(%rip), %xmm0
	call	sqrtd
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1074003968
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
