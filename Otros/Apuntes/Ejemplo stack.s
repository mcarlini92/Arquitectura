main:                       
      pushq %rbp				# Meto base pointer en el stack               
      movq  %rsp, %rbp     # Igual el stack pointer con el base pointer
      subq  $16, %rsp    	# Reservo espacio en el stack para los dos arg
      movq  $8, 8(%rsp)    # Argumentos que van al stack                       
      movq  $7, (%rsp)                          
      movl  $6, %r9d			# Los primeros 6 arg van en registros                          
      movl  $5, %r8d                          
      movl  $4, %ecx                          
      movl  $3, %edx                          
      movl  $2, %esi                           
      movl  $1, %edi
      call  f
      leave
      ret

f:
	pushq %rbp					# Guardo el rbp para poder usarlo (para poder moverme por el stack) y no perderlo
	movq  %rsp, %rbp			
	movq  %rdi, -8(%rbp)		# Guardo los registros en el stack
	movq  %rsi, -16(%rbp)
	movq  %rdx, -24(%rbp)
	movq  %rcx, -32(%rbp)
	movq  %r8, -40(%rbp)
	movq  %r9, -48(%rbp)
	movq  24(%rbp), %rax		# Guardo en rax el 8vo arg
	popq  %rbp					# Restauro el valor original de rbp
	ret							# Equivale a movq %rbp, %rsp; popq %rbp
	
/*
Estado del stack
	ret adress main
	rbp (como la recibio main)
	8
	7
	rbp (como la recibio f)
	rdi
	rsi
	rdx
	rcx
	r8
	r9
*/
