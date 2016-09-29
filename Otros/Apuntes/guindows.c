#include <stdlib.h>
#include <setjmp.h>

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
