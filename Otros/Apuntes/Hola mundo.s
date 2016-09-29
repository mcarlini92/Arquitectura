.data
s: .asciz "Hola mundo\n";
.text
.global main
main:
	movq s, %rax
	ret

// #gcc -g [NAME].s -p [NAME]
// print &s (imprime dir de memoria)
// x/s [DIR] (imprime lo que hay en esa dir como string)

