#include <stdio.h>

main (){
	int a=0x0a0b0c0d;
	char *b=(char *) &a;
	int i;
	
	printf("0x%08x\n", a);
	for(i=0; i<sizeof(a);i++){
		printf("%d: 0x%02hhx\n", i, *(b++));
	}
	
	return 0;
}

/*
Ordenamiento de byes en memoria

int a= 0x0a 0b 0c 0d
int a : |0a|0b|0c|0d|
		 31				0

&a -> 0d	
&(a+1) -> 0c		
&(a+2) -> 0b
&(a+3) -> 0a

printf("0x%08x\n", a)

%0 : ceros a la izquierda
8 	: 8 digitos
x	: hex  
*/

