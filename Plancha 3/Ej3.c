#include <stdio.h>

int solve(float a, float b, float c, float d, float e, float f, float *x, float *y);

int main(){
	float a, b, c, d, e, f;
	float *x = &a;	// Inicializo
	float *y = &a;	// Inicializo
	a = 3;
	b = 1;
	c = 9; 
	d = 2; 
	e = 3; 
	f = 13;
	printf("%f(X) + %f(Y) = %f\n", a, b, c);
	printf("%f(X) + %f(Y) = %f\n", d, e, f);
	if(solve(a, b, c, d, e, f, x, y) == 0){
		printf("Unica solucion\n");
		printf("Resultado: X = %d ; Y = %d\n", (int)*x, (int)*y);
	}
	else
		printf("Error\n");
;	return 0;
}

/*
3x+1y = 9
2x+3y = 13

x = ((9*3)-(1*13)) / ((3*3)-(1*2)) = 2
y = ((3*13)-(9*2)) / ((3*3)-(1*2)) = 3

*/
