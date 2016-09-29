# Posible implementación del siguiente programa

# f(long a1, long a2, long a3, long a4, long a5, long a6, long a7, long a8) {
#	return a8;
# }
#
# main() {
#	return f(1,2,3,4,5,6,7,8);
# }

.text

f:  # argumentos en rdi,rci,rdx,rcx,r8,r9 + stack (push 8, push 7)
	movq 16(%rsp), %rax # return a8
	ret

.global main
main:

#Cargar argumentos que van al stack

cargar_pila:			# Los demas arg van al stack de derecha a izq 
	pushq 	$8			# 1 oper arit + 1 mov
	pushq 	$7			# 1 oper arit + 1 mov

# O (lo que es lo mismo), mas eficiente 
#	subq	$16, %rsp	# 1 oper arit
#	movq	$8, 8(%rsp)	# 1 mov
#	movq	$7, (%rsp)	# 1 mov

cargar_regs:			# Los 6 primeros arg van a registros de izq a derecha
	movl	$6, %r9d 	# Al usar movl, solo estoy usando la parte de baja (32 bits)
	movl	$5, %r8d		# movl me rellena la parte alta con 0 
	movl	$4, %ecx
	movl	$3, %edx
	movl	$2, %esi
	movl	$1, %edi
	
callf:
	  call f

deshace_pila:			# Posr los dos pushq en la linea 22 (7to y 8vo arg)
	addq	$16, %rsp	# Mas eficiente, no uso un reg auxiliar

#O (lo que es casi lo mismo)
#popq %rcx
#popq %rcx

retorna:
	ret
	
/*
 - La funciona llamante es la que se encarga de preparar los argumentos y tambien de liberar el espacio usado por esta en el stack
 - En general, los valores que han sido desapilados es porque no se usaran mas y por lo tanto no se puede garantizar que sigan estando ahi ya que el SO u otras 	funciones podrian usar el stack para sus tareas
 - En la linea linea 27, se podria haber movq $8, -8(%rsp); movq $7, -16(%rsp); subq $16, %rsp pero si se produce una interrupcion, al haber dejado para lo 		ultimo el aumento del rsp, esos dos elementos se podrian perder ya que no estaban dentro de mi stack
 - En x86_64, el stack tiene una zona roja (128 bits) debajo del valor actual del rsp que una funcion puede utilizar como almacenamiento temporario (siempre que 	no llame a otras funciones o asi misma)
 */
