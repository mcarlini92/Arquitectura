#include <stdio.h>

int bforce(char *S, char *s, int lS, int ls);

int main()
{
	printf("Posicion: %d\n", bforce("Esto es una frase", "es una", 16, 6));	
	return 0;
}
