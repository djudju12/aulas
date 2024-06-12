	.file	"dmin.c"
	.text
	.globl	dmin
	.type	dmin, @function
dmin:
.LFB23:
	.cfi_startproc
	endbr64
	comisd	%xmm0, %xmm1
	jbe	.L2
	movapd	%xmm0, %xmm1
.L2:
	movapd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	dmin, .-dmin
	.globl	dmin_asm
	.type	dmin_asm, @function
dmin_asm:
.LFB24:
	.cfi_startproc
	endbr64
	movapd	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
#APP
# 13 "dmin.c" 1
	vminsd %xmm2,%xmm1
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE24:
	.size	dmin_asm, .-dmin_asm
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"%lf\n"
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
	movq	.LC1(%rip), %rax
	movq	%rax, %xmm1
	movq	.LC2(%rip), %rax
	movq	%rax, %xmm0
	call	dmin
	leaq	.LC3(%rip), %rbx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk@PLT
	movq	.LC1(%rip), %rax
	movq	%rax, %xmm1
	movq	.LC2(%rip), %rax
	movq	%rax, %xmm0
	call	dmin_asm
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1076035584
	.align 8
.LC2:
	.long	0
	.long	1076166656
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
