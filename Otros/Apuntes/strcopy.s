.data
dst:	.quad 0
src:   .quad 0
dummy:  .quad 0
len:	   .quad 0

.text
.global strcpy2
	.strcpy2:
		cmpq $0, %rcx
		je fin
bucle:		
		lodsb
		addq	$1, %rdi
		addq  $1, %rsi
		loop bucle

fin:
		xorq %rax, %rax
		ret

/*
int strcpy2(char *dst(rdi), char *src(rsi), int dummy(rdx), int len(rcx))
	-La variable dummy es para que la long entre en rcx
--------------
La instruccion loop tiene dos efectos:            
  -Decrementa en uno el registro rcx        
  -Luego, salta a la etiqueta solo si el resultado de decrementar rcx dio distinto de
   cero. Si el resultado dio cero, el flujo del programa sigue en la siguiente instruccion al loop.
----------------
movs: Copia el dato (%rsi) (puntero) en (%rdi) e incrementa/decrementa ambos registros en la cantidad del tamaño del dato

movsl =	movl	(%rsi), %rax
		 	movl	%rax, (%rdi)
		 	addq	$4, %rdi
		 	addq  $4, %rsi
------------------------
Las instrucciones de cadena incrementan/decrementan los registros rsi, rdi dependiendo de la DF del registro flags, donde aumentara si DF=0 o drecrementara si DF=1
Esta bandera se modifica con
	cld -> Clear direction -> DF=0 
	std -> Set direction -> DF=1

La DF es un "recurso" callee saved (debe ser guardado) y por convencion de llamada, es 0 al entrar a una funcion
*/
