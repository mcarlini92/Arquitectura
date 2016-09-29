.data
s:	.asciz "Hola\n"
.text
.global main
main:
	movq $0, %rax /*En rax debo poner la cant de arg en pto flotante por la func printf*/
	movq $s, %rdi # Con $ guarda en rdi la dir / Sin el peso en rdi estaria la "H"*/
	call printf /*Definida en la libreria C*/
	movq $0, %rax /*Es necesario ya que printf seguramente modifique rax*/
	ret
	
/*
int main()
{
	printf("Hola");
	return 0;
}
*/
