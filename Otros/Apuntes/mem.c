#include <stdio.h>
#include <stdlib.h>

int a; //(1)
double b; //(1)
int c=10; //(2)
char *ch="Hola mundo"; //(2)
char d; //(1)
char e; //(1)
char h='a'; //(2)

f(int arg){
	int a; double b;
	printf("f:   &a: %p, &b: %p, &arg: %p\n",&a,&b,&arg);
	g(arg);
	return 0;
}

g(int arg){
	int a; double b;
	printf("g:   &a: %p, &b: %p, &arg: %p\n",&a,&b,&arg);
	return 0;
}

main(){
	int *m1, *m2;
	m1 = malloc(sizeof(int));
	m2 = malloc(sizeof(int));

	printf("Main: main: %p, f: %p g: %p, printf: %p\n", main, f, g, printf);
	printf("Main:    &a: %p, &b: %p\n",&a,&b);
	printf("Main:   m1: %p,m2: %p\n",m1,m2);
	printf("Main: 	 &c: %p, &ch: %p, ch: %p\n", &c, &ch, ch);
	printf("Main: 	 &d: %p, &e: %p, &h: %p\n", &d, &e, &h);
	f(10);
	g(20);
}

/*
(1)-> Se guardan en memoria a una distancia cercana entre si 
(2)-> Al ser valores inicializados, se guardan en memoria a una distancia cercana entre si

Memoria

---------
funciones
---------
malloc
---------
c,d,e
---------
Hola mundo \0 (en ASCII, caracter juntos con diferencia de un bit)
---------
main
---------
g
---------
f
---------
printf
---------

Distribucion de la memoria:

Segmento de texto: Contiene codigo maquina para las funciones y suele estar en las direcciones mas bajas de memoria. En x86_64, en la configuracion mas usual el segmento de codigo comienza en 0x40000. Todos los procesos (salvo el SO) trabajan con una memoria virtual: disponen de un rango determinado de direcciones a la que pueden acceder como si fuera una gran memoria continua.

Luego del seg de texto vienen segmentos de datos. x86_64 usa datos inicializados y datos sin inicializar. Luego hay memoria dinamica (Ej malloc), a este segmento (que se extiende a medida que pido memoria) se lo llama heap(monticulo)

Al tope del espacio de direcciones esta el segmento de pila. La pila mantiene informacion sobre las llamadas a funcion y usualmente crece hacia direcciones mas bajas (push) *Mirar modelo de memoria en apunte transp_arq_x86_64*
*/
