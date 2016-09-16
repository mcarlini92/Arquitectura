#include <stdio.h>

float det(float a, float b, float c, float d);

int main()
{

	float a=2.0, b=3.0, c=5.0, d=7.0;
	float res = det(a, b, c, d);
	printf("Resultado: %f\n", res);
	
	return 0;
}
