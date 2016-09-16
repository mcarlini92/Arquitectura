#include <stdio.h>
#include <stdlib.h>

typedef struct my_float{	
	unsigned int s:1;
	unsigned int e:16;
	unsigned int f:18;
} myfloat;

myfloat sum(myfloat x, myfloat y){	
	myfloat z;
	z.s = 0;
	unsigned int xux = x.e - y.e; 
	// Alineo mantisas
	if(xux > 0){
		 y.f = y.f >> xux; 
		 z.e = x.e;
	}
	else {
		x.f = x.f >> (-xux);
		z.e = y.e;
	}	
	z.f = x.f + y.f; // Sumo mxntisas
	// Normalizo
	while ( z.f & (1<<18)){
		z.e += 1;
		z.f = z.f >> 1;
	}
	return z;
}

myfloat mul(myfloat x, myfloat y){
	myfloat z;
	if((x.s + y.s) > 0)
		z.s = 1;
	else
		z.s = 0;
	
	z.f = x.f * y.f; // Multiplico mantisas
	z.e = x.e + y.e; // Sumo exponentes
}

int main() {
	myfloat a,b,c,d;
	a.s = 0;
	a.e = 30000;
	a.f = 21;
	b.s = 0;
	b.e = 30000;
	b.f = 23;
	c = sum(a,b);
	printf("Suma \n");
	printf("Signo: %d\n", c.s);
	printf("Exponente: %d\n", c.e);
	printf("Mantisa: %d\n\n", c.f);
	d = mul(a,b);
	printf("Multiplicacion \n");
	printf("Signo: %d\n", d.s);
	printf("Exponente: %d\n", d.e);
	printf("Mantisa: %d\n", d.f);
}

/*
Suma o resta
1. Chequear por ceros
2. Alinear las mantisas
3. Sumar o restar las mantisas
4. Normalizar el resultado

Multiplicacion
1. Chequear por ceros.
2. Sumar los exponentes.
3. Multiplicar las mantisas.
4. Normalizar el producto.
*/
