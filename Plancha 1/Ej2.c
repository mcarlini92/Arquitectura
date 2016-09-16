#include <stdio.h>
#include <gmp.h>

typedef struct {
	short n[16];
} nro;

void print(nro n)
{
		int i;
		char str[1024];
		short sign[16], num[16];
		mpz_t n1, n2;
		for (i=0; i<15; i++) {
				num[i] = n.n[i];
				sign[i] = 0;
		}
		num[15] = n.n[15] & 0x7FFF;
		sign[15] = n.n[15] & 0x8000;
		mpz_init(n1);
		mpz_init(n2);
		mpz_import(n1, 16, -1, 2, 0, 0, num);
		mpz_import(n2, 16, -1, 2, 0, 0, sign);
		mpz_neg(n2, n2);
		mpz_add(n2, n1, n2);
		mpz_get_str(str, 10, n2);
		printf("Numero: %s\n", str);
		mpz_clear(n1);
		mpz_clear(n2);
}

int compare(nro x, nro y){
    int i;
    for(i=0;i<16;i++)
        if(x.n[i] != y.n[i])
            return 0;
    return 1;
}

int isEven(nro x)
{
	return (x.n[0] & 1);
}

nro roll_l(nro x)
{
   int i;
	int carryflag = 0, auxcarry = 0;
	
	for (i=0; i<16; i++)
	{
		auxcarry = x.n[i] & 0x8000; // Compruebo si hay acarreo al prox short
		x.n[i] <<= 1;	// Corrimiento con asignacion
		if (carryflag)	// Si tengo acarreo del short anterior  
		    x.n[i] |= 1;
	
		carryflag = auxcarry; // Actualizo la bandera de carry
	}
    return x;
}

nro roll_r(nro x)
{
	int i;
	int auxcarry = 0, carryflag = 0;	
	auxcarry = x.n[15] & 1;	// Compruebo si hay acarreo al prox short 
	x.n[15] >>= 1;	// Corrimiento con asignacion, rellena con el bit mas significativo 
	carryflag = auxcarry;
	
	for (i=14; i>=0; i--) // Realizo el mismo procedimieno que antes
	{
		auxcarry = x.n[i] & 1;	// Compruebo si hay acarreo al prox short 
		x.n[i] >>= 1;
		if (carryflag)	// Si tengo acarreo del short anterior
			x.n[i] |= 0x8000; 
	 
		carryflag = auxcarry; // Actualizo la bandera de carry
	}
    return x;
}

nro sum(nro x, nro y){
	nro aux;
	unsigned int carry = 0, i;

	for(i=0 ;i<16; i++){
		int suma = (unsigned short)x.n[i] + carry + (unsigned short)y.n[i]; // Suma mas acarreo
		aux.n[i] = suma; // Suma es int, al asignarle un short copia la parte menos sign
		carry = suma >> sizeof(short)*8; // El acarreo es la parte más significativa de suma
	}
	return aux;
}

int main()
{
	int i;
	nro n1, n2; 
	for (i=0; i<16; i++)
	{ 
		n1.n[i] = 0;
		n2.n[i] = 0;
	}
	n1.n[0] = 21;
	n2.n[0] = 42;
	print(n1);
	print(n2);
	print(roll_l(n1));
	print(roll_r(n2));
	compare(n1, n2);
	printf("Par: %d\n", isEven(n1));
	printf("Par: %d\n", isEven(n2));
	print(sum(n1, n2));
return 0;	
}

// Compilar con gcc -lgmp