#include <stdio.h>
#include <string.h>

unsigned int rpa(unsigned int a, unsigned int b){
	switch (b) {
		case 0:
			return 0;
		case 1:
			return a;
		default:
		if (b % 2 == 0)  // Si b es par
			return rpa(a << 1, b >> 1);
		else 
			return rpa(a << 1, b >> 1) + a; // Si b es impar
	}
}
// 2a -> a << 1
// b/2 -> b >> 1
// Multiplico a 'a', divido a 'b' y vuelvo a llamar a la funcion

int main() {
	unsigned int x, y;
	printf("1er nro: ");
	scanf("%d", &x);
	printf("2do nro: ");
	scanf("%d", &y);
	printf("\nRPA(%d,%d) = %d\n", x, y, rpa(x,y));
	
return 0;
}
