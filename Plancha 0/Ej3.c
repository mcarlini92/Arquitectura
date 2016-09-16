#include <stdio.h>

int isOne (long int n, int b)
{
    return ( (n>>b) & 1);   
}

void printbin (long int n)
{
    int i;
    for(i=8*sizeof(long int)-1; i>=0; i--) // (1) 
        printf("%d", isOne(n, i) ? 1:0);
}

int main ()
{
    long int n;
    printf("Numero: ");
    scanf("%i", &n);
    printbin(n);
    printf("\n");
    return 0;
}

/*
(1) Usamos 8*sizeof(long int) para que funcione en cualquiera arq
*/
