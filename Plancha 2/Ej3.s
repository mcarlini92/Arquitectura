.data
S: .quad 0
s:  .quad 0
lS:  .quad 0
ls:	  .quad 0

.text
.global bforce

bforce:
	movq %rdi, S		# S = cadena en la que se buscara 's'
	movq %rsi, s		# s = cadena a buscar en 'S' 
	movq %rdx, lS		# lS = long de 'S'
	movq %rcx, ls		# ls = long de 's'
	
	lodsb 				# Guardo en %al el 1er caracter de 's'(Equivale a movb (%rsi), %al ; incq %rsi )
	subq %rcx, %rdx 	
	movq %rdx, %rcx		
	incq %rcx			# rcx = lS-ls+1 
	
buscar:									
	repne scasb 		# Compara %al con %rdi y va incrementando rdi si no coincide
						# Si lo encontro, rdi apuntara al siguiente caracter ya que fue aumentado por scasb
	jne no_encontrado	# Si no lo encuentra, termino
	
	movq %rcx, %r8		# Guardo mi posicion en 'S' por si luego no coinciden los demas caracteres que faltan
	movq %rdi, %r9
	movq %rsi, %r10
	
	movq ls, %rcx		
	decq %rcx			# rcx = ls-1 ('s' menos el 1er caract ya encontrado)
	
	repe cmpsb			# Compara lo apuntado por rdi y rsi mientras sean iguales o rcx veces
						# Para diferenciar porque causa termino usamos rflags 
						
	je encontrado		# Si coinciden los demas caracteres de 's', termino 
	
	movq %r8, %rcx		# Si no coinciden los demas caract, restablezco para poder continuar 
	movq %r9, %rdi
	movq %r10, %rsi
		
	jmp	buscar			# Comienzo de nuevo
	
no_encontrado:
	movq $-1, %rax		# Retorno -1
	ret
	
encontrado:	
	movq %r9, %rax		# Si lo encontró, devuelve la posicion en 'S' del 1er caract de 's'
	movq S, %rcx
	subq %rcx, %rax
	ret
	
/*
int fuerzabruta(char *S(rdi), char *s(rsi), int lS(rcx), int ls(rdx)){
	int i, j;
	for(i=0; i<lS-ls+1; i++){
		if(S[i]==s[0]){
			for(j=0; j<ls && S[i+j]==s[j]; j++);
				if(j==ls)
					return i;
		}
	}
	return -1;
}

- scas (de scan string) compara lo apuntado por rdi con el valor del registro rax (o del sub-registro segun corresponda) e incrementa/decrementa rdi en la cantidad de bytes dada por el sufijo de tipo

- 

*/
