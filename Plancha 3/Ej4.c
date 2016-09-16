#include <stdio.h>

void sum(float *a, float *b, int len);

int main(){
	float a[] ={3.1, 3.2, 3.3};
	float b[] ={3.1, 3.2, 3.3};
	int i = 0;
	int len = 3;
	sum(a, b, len);
	for(i=0;i<len;i++)
		printf("%f\n", a[i]); 
	return 0;
}

