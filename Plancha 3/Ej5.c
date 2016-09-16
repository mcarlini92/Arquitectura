#include <stdio.h>

void sum_sse(float *a, float *b, int len);

int main(){
	float a[] ={3.1, 3.2, 3.3, 3.4};
	float b[] ={3.1, 3.2, 3.3, 3.4};
	int i = 0;
	int len = 4;
	sum_sse(a, b, len);
	for(i=0;i<4;i++)
		printf("%f\n", a[i]); 
	return 0;
}
