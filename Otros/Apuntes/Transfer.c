
void ft1() // t1
{
	double d;
	for(d=-1;;d+=0.001)
	{
		printf("%f\n", d);
		TRANSFER(t1, t2);
	}	
}

void ft2() // t2
{
	int i;
	for(i=i; i<10000; i++)
	{
		printf("%d\n", i);
		TRANSFER(t2, t1);
	}
	TRANSFER(t1, taskmain);
}


Corrutinas:
				
Usaremos como ejemplo dos funciones que deben avanzar en sus calculos "simultaneamente". Un ejemplo es: ls | grep "exp" (busca la expresion "exp" en la carpeta). La idea es que ft1 y ft2 se vayan turnando para ir realizando sus calculos. 

Para esto podriamos usar jump/ goto (con etiquetas) pero hay un problema, C no permite saltar a etiquetas de otras funciones y si lo intentaramos hacer embebiendo un jmp tampoco serviria ya que el jmp no cambia el rsp y el rbp, con lo que los accesos a variables automaticas, temporales, return adress y argumentos seran erroneos.

Otra posibilidad es usar llamadas a funciones (call y ret en assembler) pero ft2 no continuaria se ejecucion anterior, por lo que ft2 nunca progresaria ya que estaria siempre empezando desde el comienzo (valga la redundancia)

La solucion es usar setjmp y longjmp: la idea es que ft1 avanze un poco, luego hago un setjmp para guarda el estado y dsp hago un longjmp para que tome el control ft2 para que esta avanze un poco, luego hago un setjmp para guarda el progreso y dsp hago un longjmp para que tome el control ft1, y asi es el ciclo

Luego el TRANSFER (que permite ceder la ejecucion temporalemente a otra tarea - en C seran funciones) sera entonces 
	
	TRANSFER(o, d) equivale a ((setjmp(0) == 0 ? (longjmp(d, 1), 0) : 0 )) donde o y d son jumpbuffer
	
Antes de usar TRANSFER, obligatoriamente tengo que haber usado setjmp, podriamos hacer en el main:
	
	#if (setjmp(t1) != 0) ft1;
	if (setjmp(t2) != 0)
		ft2;
	ft1();
		...
		TRANSFER(t1, t2);
		
Pero todavia seguimos teniendo otro problema, el marco de act de ft1 podria pisar el marco de act de ft2. Para evitar esto, podemos dejar un espacio entre el fin de marco de act de ft1 y el comienzo del marco de ft2

¿Qué ocurre si tengo que organizar un nro grande de corrutinas?, tengo que organizar los TRANSFER para que todas las corrutinas puedan avanzar. Una secuencia posible seria A->B; B->C; C->A y de esta manera formar un ciclo.

¿Como puedo hacer para que A avance mas rapido que las otras tareas?, podriamos hacer:

void fA(){
	double d;
	for(d=-1;;d*=0.001){
		printf("d=%f\n", d);
		if(((int)d*1000)%2)
			TRANSFER(A, B);
	}
}

Gestionar la logica de los TRANSFER en cada corrutina se hace complicado. La idea es hacer una corrutina que centralice la logica de los TRANSFER. De esta forma, la administracion de la ejecucion de las tareas se hace en un solo punto del programa. 

Las corrutinas, cuando deciden ceder la ejecucion haran YIELD para que la logica centralizada (planificador o scheduler) pueda decidir que corrutina seguira ejecutando.

Asi, ft1() quedara:

void ft1(){
	double d;
	for(d=-1;;d*=0.001){
		printf("d=%f\n", d);
		YIELD(t1);	// Hara un longjmp al planificador
	}
}

El planificador sera:

void schedfunc(){
	for(;;){
		ACTIVATE(t1);
		ACTIVATE(t2);
	}
}
 
En donde, ACTIVATE y YIELD se definiran como:
# define ACTIVATE(d) TRANSFER(schedt, d) // Tarea asociada a schedfunc ; d <- destino
# define YIELD(o) TRANSFER(o, schedt)	// o <- origen

Si queremos darle mas tiempo de ejecucion a t1, podemos hacer:
	
for(;;){
	ACTIVATE(t1);
	ACTIVATE(t1);
	ACTIVATE(t2);
	ACTIVATE(t3);
}

Obs: Ahora, agregar una nueva tarea o darle mas tiempo a alguna tarea es facil, solo hay que modificar el planificador
	
El codigo del main sera:

task t1, t2, taskmain, schedt

	... (codigo de las t1, t2, ...)

	main(){
	stack(schedt, schedfunc);
	stack(t1, ft1);
	stack(t2, ft2);
	YIELD(taskmain);
	return 0;	
	}

Este esquema de trabajo colaborativo se utilizo en algunos sistemas operativos como en Windows 3.1 (multitarea cooperativa). ¿Que problema puede traer?.
Ej:
	for(;;); // Un programa mal hecho o malicioso podria arruinar toda la multitarea

Los sistemas operativos modernos usan un modo de multirarea apropiativa, o sea, un proceso ejecuta algunas intrucciones y luego el SO cambia a otros procesos (sin que el proceso inicial lo sepa). Cuando se retome la ejecucion habra que restaurar TODOS los registros (no solo las callee saves).

Usaremos un mecanismo de señales (que provee el SO) para simular las interrupciones del reloj (que usa un SO real). Una señal es un evento asincrono que puede recibir un proceso y a determinados eventos se les puede asociar una accion. Un ejemplo de esto es el ^C (Ctrl+C) que normalmente interrumpe un proceso. Lo que hace el SO es enviar una señal SIGINT, la cual podemos capturar e ignorar.

Ej:
#include <signal.h>
main(){
	signal(SIGINT, SIG_IGN);
	for(;;);
}

Hay acciones predifinidas:
	SIG_IGN <- ignorar la señal
	SIG_DFL <- resturar el comportamiento predeterminado

Signal nos permite asociar una accion a determinada señal (evento). La funcion signal se solia definir asi:
void (*signal(int sig, void (*pf)(int))(int)); 
// Signal es una funcion que toma un entero sig (nro de señal) y pt (un puntero a funcion  que toma un entero y devuelve void) y devuelve una funcion que toma un entero y devuelve void

Uso: signal(nro_de_señal, accion) -(retorno)-> void (x)(int), accion asociada anteriormente a la funcion (por si hay que dejar las cosas como estaban)

Ej:
#include <stdio.h>
#include <signal.h>
void handler(int n){
	printf("Auch\n");
}

main(){
	signal(SIGINT, handler); // Cuando se reciba la señal SIGINT (C^), se ejecutara la funcion handler
	for(;;);
}

Obs: SIGKILL no puede ser capturada, por lo que siempre funcionara para poder interrumpir programas

Podemos hacer un programa que soporte tres ^C y al cuarto sea interrumpido, solo hay que modificar el handler

void handler(int n){
	static int i=0;
	printf("Sig: %d, van %d veces\n", n, i+1);
	if(++i>3)
		signal(n, SIG_DFL);
}

La funcion kill(int pid, int signal) envia la señal signal al proceso pid. La funcion raise(int signal) equivale a kill(int pid, int signal).

Ej:
#include <stdio.h>
#include <signal.h>

void handler(int n){
	static int i=0;
	printf("\nSig: %d, van %d veces\n", n, i+1);
	if(++i>3)
		signal(n, SIG_DFL);
}

main(){
	signal(SIGINT, handler);
	kill(getpid(), SIGINT);
	//raise(SIGINT);
	for(;;);
}

Luego de ejecutar el handler, el proceso continua su ejecucion normal. Si en el handler ponemos un YIELD, podriamos hacer cambios transparentes pero no queremos que el usuario tenga que hacer ^C o enviar señales con el comando kill. Usaremos (en vez de C^) la señal de un temporalizador: SIGALRM, esta llega cuando se cumple el tiempo especificado en la ultima llamada a alarm. Por lo tanto, alarm(5) enviara al proceso actual una señal SIGALRM dentro de 5 segundos.

Ej:
#include <stdio.h>
#include <signal.h>

void alarma(int n){
	printf("Alarma");
	alarm(5);	
}

main(){
	signal(SIGALRM, alarma);
	alarm(5);
	for(;;){
		printf("a\n");
		sleep(1);			
	}
}

Otra señal es SIGSEGV, que esta asociada a fallos de segmentacion. (Ejercicio: hacer un programa que detecte un segfault (y solucionarlo si es posible))

Para hacer que las corrutinas cambien automaticamente, puedo poner alarmas y en la accion asociada hacer YIELD.

Ej:
#include <stdio.h>
#include <signal.h>
#include "guindows.h"
task t1, t2, taskmain, tsched;
static int i;

void fsched(){
	for(;;){
		if(i++%2)
			ACTIVATE(t1);
		else
			ACTIVATE(t2);
	}
}

void ft1(){
	for(;;)
		printf("Soy t1\n"); // YIELD no estan porque van a hacer interrumpidos por la alarma 
}

void ft2(){
	for(;;)
		printf("Soy t2\n"); // YIELD no estan porque van a hacer interrumpidos por la alarma 
}

void handler(int sig){
	alarm(1);
	if(i%2)
		YIELD(t2);
	else
		YIELD(t1);
}

main(){
	stack(t1, ft1);
	stack(t2, ft2);
	stack(t1, ft1);
	stack(tsched, fsched);
	signal(SIGALRM, handler);
	alarm(1);
	TRANSFER(taskmain, t1);
	return 0;
}

Un SO moderno suele usar un mecanismo similar (basado en temporalizadores e interrupciones) para proveer multitarea. A esto se lo llama multitarea apropiativa (los procesos no se enteran ni tienen que hacer nada para convivir con otros procesos, por eso no incluyen el YIELD).
El SO cambia de tarea de prepo (preempt) y de forma transparente.
