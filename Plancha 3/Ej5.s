.data	
.text
.global sum_sse
sum_sse:
	movq %rdx, %rcx 		#%rcx <- len
bucle:
	movaps (%rdi), %xmm0
	movaps (%rsi), %xmm1
	addps %xmm1, %xmm0
	movaps %xmm0, (%rdi)
	addq $16, %rdi
	addq $16, %rsi
	subq $3, %rcx			#Loop resta de a uno pero yo necesito restar de a 4 
	loop bucle				#Considerar cuando no es mult de 4
	xorq %rax, %rax
	ret

