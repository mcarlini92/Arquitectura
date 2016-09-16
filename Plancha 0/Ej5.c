#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

void swap3(int *a, int *b, int *c)
{
	swap(a, b);		
	swap(a, c);
}

int main ()
{
    int a, b, c;
    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);
    printf("c: ");
    scanf("%d", &c);
    swap3(&a, &b, &c);
    printf("\na: %d \nb: %d \nc: %d \n", a, b, c);   
    return 0;
}

// Este programa aprovechar el xor para no utilizar variables aux.
