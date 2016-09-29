.data
s:	.asciz "%ld\n"
.text
.global main
main:
	movq $0, rax /*En rax debo poner la cant de arg en pto flotante por la func printf*/
	movq $s, %rdi 
	movq $3, rsi 
	call printf /*Definida en la libreria C*/
	movq $0, rax /*Es necesario ya que printf seguramente modifique rax*/
	ret
	
/*
int main()
{
	printf("%ld\n", 3);
	return 0;
}
*/
