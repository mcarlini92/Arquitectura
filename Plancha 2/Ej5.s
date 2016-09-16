.data
.text  
.global setjmp2
setjmp2:
	movq %rbx, (%rdi)	# Guardo los callee saves en el arreglo que paso por arg
	movq %r10, 8(%rdi)
	movq %r13, 16(%rdi)
	movq %r14, 24(%rdi)
	movq %r15, 32(%rdi)
	movq %rbp, 40(%rdi)
	movq %rsp, 48(%rdi)
	movq (%rsp), %rax	# Como no puedo mover de mem a mem, lo hago usando un reg aux
	movq %rax, 56(%rdi)	# y la guardo. En 56(%rdi) tengo la return adress
	ret

.global longjmp2
longjmp2:
	movq (%rdi), %rbx	# Restauro argumentos
	movq 8(%rdi), %r10 
	movq 16(%rdi), %r13 
	movq 24(%rdi), %r14 
	movq 32(%rdi), %r15 
	movq 40(%rdi), %rbp 
	movq 48(%rdi), %rsp
	movq 56(%rdi), %rcx 
	movq %rcx, (%rsp)	# Reemplazo (piso) la return adress en el stack por la que guarde en 56(%rdi), que ahora esta en rcx
	
	cmpq $0, %rsi
	jnz end				# Si 2do != 0, devuelvo ese valor
	movq $1, %rsi		# Si 2do = 0, devuelvo 1
	
end:
	movq %rsi, %rax	
	ret
/*
setjmp:

int setjmp(jmp_buf environment(en rdi));
Saves the environment into the variable environment. If a non-zero value is returned, then this indicates that the point in the sourcecode was reached by a longjmp. Otherwise zero is returned indicating the environment has been saved.

longjmp:

void longjmp(jmp_buf environment(en rdi), int value(en rsi));
Causes the environment to be restored from a setjmp call where the environment variable had been saved. It causes execution to goto the setjmp location as if setjmp had returned the value of the variable value. The variable value cannot be zero. However, if zero is passed, then 1 is replaced. If the function where setjmp was called has terminated, then the results are undefined.
 
*/
