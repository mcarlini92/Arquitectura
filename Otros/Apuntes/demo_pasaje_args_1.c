#include <stdio.h>

main(){
	char a=28;
	printf("%d %d\n",printf("1\n"),printf("2\n"));
	printf("%d %d\n",a=a+1,a=a+1);
}

/*
 Resultado:
 
 2
 1
 2 2 (Retorno de printf, cant de arg)
 30 29	
 Los argumentos se evaluan de derecha a izquierda
*/
