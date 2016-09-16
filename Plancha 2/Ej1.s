.data
	fmt: .asciz "%ld\n"
	i: .quad 0xdeadbeef
.text
.global main
main:
     movq $fmt, %rdi # el primer argumento es el formato
     movq $1234, %rsi # el valor a imprimir
     xorq %rax, %rax # cantidad de valores de punto flotante
     call printf
     ret

/*
(1)	movq %rsp, %rsi -> Imprimira el valor del registro de rsp

(2)	movq $fmt, %rsi -> Imprimira la direccion de la cadena de formato

(3)	movq $fmt, %rsi 
	fmt: .asciz "%x\n" -> Imprimira la direccion de la cadena de formato hexa
	
(4)	movq (%rsp), %rsi -> Imprimira el valor de rsp

(5)	movq 8(%rsp), %rsi -> Imprimira el valor de rsp+8

(6)	movq i, %rsi -> Imprimira el valor i

(7)	movq $i, %rsi -> Imprimira la direccion de i
*/
