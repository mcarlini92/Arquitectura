#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int clave = atoi(argv[1]);
	int caract;
	char xor;
	while ((caract = getchar()) != EOF)
	{
		xor = (caract ^ clave);
		printf("%c, xor");
	}
	return 0;
}
