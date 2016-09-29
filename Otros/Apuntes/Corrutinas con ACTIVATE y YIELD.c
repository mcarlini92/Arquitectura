#include <stdio.h>
#include "guindows.h"
# define ACTIVATE(d) TRANSFER(schedt, d) // Tarea asociada a schedfunc ; d <- destino
# define YIELD(o) TRANSFER(o, schedt)	// o <- origen

task t1, t2, t3, t4, taskmain, schedt;

void ft1(){
	for(;;){
		printf("Soy ft1");
		YIELD(t1);		
	}
}

void ft2(){
	for(;;){
		printf("Soy ft2");
		YIELD(t2);
	}
}

void ft3(){
	for(;;){
		printf("Soy ft3");
		YIELD(t3);
	}
}

void ft4(){
	for(;;){
		printf("Soy ft4");
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
