.data
	i: .quad -1
	s: .asciz "\n%d tiene %ld bits en 1\n"
.text
.global	main

main:
	movq $0, %rdx		# Contador de posicion
	movq $0, %rcx		# Contador de bits en 1
	movq i, %rax		# i

bucle:	
	cmpq $64, %rdx		# Me fijo en que posicion estoy
	je	fin				# Si ya recorri todos los bits, termino (je = jump equal)
							# En caso contrario ....
	rolq %rax 			# rota los bits de i, dejando el bit mas significativo en la bandera de acarreo
	adc	$0, %rcx 		# adc opo, opd calcula opd opo+opd+CARRY (sumo 1 si hubo acarreo)
	incq %rdx 			# Incremento cont de posicion
	jmp	bucle			# Repito el bucle hasta terminar
	
fin:
	movq $s, %rdi			# 1er arg
	movl i, %esi			# 2do arg
	movq %rcx, %rdx		# 3er arg
	xorq %rax, %rax		# Args en pto flotante = 0
	call printf
	xorq %rax, %rax		# Aunque printf modifique rax, retorno 0
	ret
	

