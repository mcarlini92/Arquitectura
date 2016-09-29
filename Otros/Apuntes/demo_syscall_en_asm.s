.text
.global main
main:
	movq $60, %rax
	movq $10, %rdi
	syscall
	
	movq $0, %rax
	ret
