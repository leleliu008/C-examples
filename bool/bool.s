	.file	"bool.c"
	.section	.rodata
.LC0:
	.string	"sizeof(bool) = %lu\n"
.LC1:
	.string	"isXXX = %d\n"
.LC2:
	.string	"isYYY = %d\n"
.LC3:
	.string	"isZZZ = %d\n"
.LC4:
	.string	"isVVV = %d\n"
.LC5:
	.string	"isTTT = %d\n"
.LC6:
	.string	"isNNN = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movb	$0, -6(%rbp)
	movb	$1, -5(%rbp)
	movb	$0, -4(%rbp)
	movb	$1, -3(%rbp)
	movb	$1, -2(%rbp)
	movb	$1, -1(%rbp)
	movl	$1, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movzbl	-6(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movzbl	-5(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movzbl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movzbl	-3(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movzbl	-2(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movzbl	-1(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
