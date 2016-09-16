.data	
.text
.global solve
solve:
	movss %xmm0, %xmm6		#xmm6 <- a
	mulss %xmm6, %xmm3		#xmm6 <- a*d
	movss %xmm1, %xmm7		#xmm7 <- b
	mulss %xmm7, %xmm2		#xmm7 <- b*c
	subss %xmm6, %xmm7		#xmm6 <- (a*d)-(b*c)
	movss %xmm6, %xmm8		#xmm8 <- (a*d)-(b*c)
	
    cvttss2siq %xmm8, %rdx	#rdx <- (int)xmm8
	cmpq $0, %rdx			
	je error
	
	movss %xmm4, %xmm6		#xmm6 <- e
	mulss %xmm6, %xmm3		#xmm6 <- e*d
	movss %xmm1, %xmm7		#xmm7 <- b
	mulss %xmm7, %xmm5		#xmm7 <- b*f
	subss %xmm6, %xmm7		#xmm6 <- (e*d)-(b*f)
	movss %xmm6, %xmm9		#xmm9 <- (e*d)-(b*f)
	
	movss %xmm0, %xmm6		#xmm6 <- a
	mulss %xmm6, %xmm5		#xmm6 <- a*f
	movss %xmm4, %xmm7		#xmm7 <- e
	mulss %xmm7, %xmm2		#xmm7 <- e*c
	subss %xmm6, %xmm7		#xmm6 <- (a*f)-(e*c)
	movss %xmm6, %xmm10		#xmm10 <- (a*f)-(e*c)
	
	divss %xmm9, %xmm8		#xmm9 <- ((e*d)-(b*f))/((a*d)-(b*c)
	divss %xmm10, %xmm8 	#xmm10 <- ((a*f)-(e*c))/((a*d)-(b*c))
	
	movq %xmm9, (%rdi) 	#(%rdi) <- %xmm9
	movq %xmm10, (%rsi)	#(%rsi) <- %xmm10
	
	movq $0, %rax 			#Devuelvo 0
	ret
	
error:
	movq $-1, %rax 			#Devuelvo -1
	ret


/*
aX + bY = e
cX + dY = f

Cramer:
	X = ((e*d)-(b*f)) / ((a*d)-(b*c))
	Y = ((a*f)-(e*c)) / ((a*d)-(b*c))
	
int solve(float a, float b, float c, float d, float e, float f, float *x, float *y);

a -> xmm0
b -> xmm1
c -> xmm2
d -> xmm3
e -> xmm4
f -> xmm5
x -> rdi (puntero a float)
y -> rsi (puntero a float)

cvttss2siq -> Convert with truncation single precision to quadword integer
*/
