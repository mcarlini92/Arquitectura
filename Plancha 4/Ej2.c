#include <stdio.h>

unsigned int farmer(unsigned int i, unsigned int j);

int main(){
	unsigned int i=1;
	unsigned int j=15;
	unsigned int res = farmer(i,j);
	printf("%u * %u = %u\n", i, j, res);
	return 0;
}
