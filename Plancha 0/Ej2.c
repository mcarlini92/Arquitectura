#include <stdio.h>
#include <stdlib.h>

int isOne (long int n, int b)
{
    printf("%i \n", (n>>b) & 1);
    return 0;   
}

int main ()
{
    long int n;
    int b;
    printf("Numero: ");
    scanf("%i", &n);
    printf("Bit: ");
    scanf("%d", &b);
    isOne(n, b);    
    return 0;
}
