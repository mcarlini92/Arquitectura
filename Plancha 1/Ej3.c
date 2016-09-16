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

nro rpa(nro x, nro y){
	nro cero = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // Cero de la estructura
	nro uno = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}; // Uno de la estructura
	if(compare(y, cero))
		return cero;
	if(compare(y, uno))
		return uno;
	if(isEven(y))
		return sum(rpa(roll_l(x),roll_r(y)),x);
	return rpa(roll_l(x),roll_r(y));
}

int main(){
	int i;
	nro n, m;
	
	for (i=0; i<16; i++)
	 	n.n[i] = 0;
	n.n[0] = 17;
	for (i=0; i<16; i++)
		m.n[i] = 0;
	m.n[0] = 21;
	printf("\nEl producto entre\n");
	print(n);
	print(m);
	printf("es\n");
	print(rpa(n,m));	

return 0;
}

// Compilar con gcc -lgmp
