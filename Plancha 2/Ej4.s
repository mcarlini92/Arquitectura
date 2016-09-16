.data
	fmt: .string "%d"
	entero:	.long -100
funcs:	
	.quad f1
	.quad f2
	.quad f3
	
.text
f1:	
	movl $0, %esi
	movq $fmt, %rdi
	call printf
	jmp	fin
	
f2:	
	movl $1, %esi
	movq $fmt, %rdi
	call printf
	jmp	fin
	
f3:	
	movl $2, %esi
	movq $fmt, %rdi
	call printf
	jmp	fin
	
	.globl main
main:	
	pushq	%rbp
	movq	%rsp, %rbp
	
	movq $entero, %rsi
	movq $fmt, %rdi
	xorq %rax, %rax
	call scanf
		
	xorq %rax, %rax
	# COMPLETAR CON DOS INSTRUCCIONES
	movl entero, %ecx
	movq funcs(, %rcx, 8), %rdx	#(1)
	#-------------------------------------
	jmp	*%rdx # El asterisco es necesario por sintaxis
	
fin:		
	movq %rbp, %rsp
	popq %rbp
	ret
/*
(1)	K(%reg1, %reg2, S) donde K y S son constantes enteras y S=1,2,4,8 refiere al valor reg1 + (reg2 * S + K)
	rdx <- *(funcs+(rcx*8))
*/
