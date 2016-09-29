#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

typedef jmp_buf task;
#define TRANSFER(o,d) (setjmp(o)==0 ? (longjmp(d,1),0)n : 0);
extern void stack(task, void (*pf)());

# define ACTIVATE(d) TRANSFER(schedt, d) // Tarea asociada a schedfunc ; d <- destino
# define YIELD(o) TRANSFER(o, schedt)	// o <- origen

#define TPILA 4096 
#define NPILAS 10 // Soporta hasta 10 corrutinas

static void hace_stack(jmp_buf buf, void (*pf)(), unsigned prof, char *dummy) {
	if( dummy - (char *) &prof >= prof) {
		if (setjmp(buf)!=0) {
			pf(); abort();
		}
	} else hace_stack(buf, pf, prof, dummy);
}

void stack(jmp_buf buf, void (*pf)()) // Funcion para crear marcos de act desde el ult hacia el primero
{
	static int ctas = NPILAS;
	char dummy; // variable para calcular la profundidad
	hace_stack(buf, pf, TPILA *ctas, &dummy);
	ctas--; // Empiezo con el ultimo y voy subiendo
}

task t1, t2, t3, t4, taskmain, schedt;

void ft1(){
	for(;;){
		printf("Soy ft1\n");
		YIELD(t1);		
	}
}

void ft2(){
	for(;;){
		printf("Soy ft2\n");
		YIELD(t2);
	}
}

void ft3(){
	for(;;){
		printf("Soy ft3\n");
		YIELD(t3);
	}
}

void ft4(){
	for(;;){
		printf("Soy ft4\n");
		YIELD(t4);
	}
}

void schedfunc(){
	for(;;){
		ACTIVATE(t1);
		ACTIVATE(t2);
		ACTIVATE(t3);
		ACTIVATE(t3);
		ACTIVATE(t4);
		ACTIVATE(t4);
	}
}

main(){
	stack(schedt, schedfunc);
	stack(t1, ft1);
	stack(t2, ft2);
	stack(t3, ft3);
	stack(t4, ft4);
	YIELD(taskmain);
	return 0;	
	}
