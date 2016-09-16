#include <stdio.h>
#include <stdlib.h>

int size = 8*sizeof(long int);

int isOne (long int n, int b)
{
    return ((n>>b) & 1);   
}

void printbin (long int n)
{
    int i;
    for(i=size-1; i>=0; i--) // (1) 
        printf("%d", isOne(n, i) ? 1:0);
}

void rollr (int long n)
{
   long int i = (((n>>1)) | ( isOne(n, 0)<< (size-1)));
   printbin(i);
   return;    
}

int main ()
{
    long int n;
		printf("Numero: ");
    scanf("%i", &n);
    printbin(n);
    printf("\n");
    rollr(n);
    printf("\n");   
    return 0;
}
