.data
i: .long 0
.text
	calculo_muy_complicado:
		movl i, %eax
		imull $2, %eax
		movl %eax, i
		jmp vuelve	
.global main
main:
	movq $0, i # Inicializa i = 0
cond : cmpq $1000, i
	jge fin # i >= 1000
	jmp calculo_muy_complicado
vuelve : incq i # i++
	jmp cond
fin : ret

*/
Para poder separar la funcion en otro modulo (archivo) hay que definir como global los simbolos que seran accedidos desde otro modulo (archivo)
/*

#Como retornar a la funciona llamante en el lugar correcto

.data
i: .long 0
.text
	calculo_muy_complicado:
		movl i, %eax
		imull $2, %eax
		movl %eax, i
		jmp *%rbx	
.global main
main:
	cmpq $1000, i
	jge fin
	movq $sigue, %rbx
	jmp calculo_muy_complicado 
sigue: incq i
	imp main
fin: movq $sigue2, %rba
	jmp calculo_muy_complicado
sigue2: ret
	
cond : cmpq $1000, i
	jge fin # i >= 1000
	movq $sigue, %rbx
	jmp calculo_muy_complicado
vuelve : incq i # i++
	jmp cond
fin : jmp calculo_muy_complicado
sigue2 : ret


