void f(int a, char b) {return ;}

int a(unsigned a1, char a2, unsigned char a3,
      long a4, char *a5, void (*a6)(int, char), int a7, char a8, unsigned char a9) {
	return 10;
}

unsigned b1=0;
char b2=128;
unsigned char b3 = 128;
long b4=0xaaaabbbbccccddddL;
char *b5="hola mundo\n";
int b7 = 0xffffeeee;
char b8= 128;
unsigned char b9=128;

main() {
	return a(b1,b2,b3,b4,b5,f,b7,b8,b9);
}

/*
Por convencion, cada arg tiene que ir separados en dist registros

unsigned a1 -> rdi
char a2 -> rsi
unsigned char a3 -> rdx
long a4 -> rcx
char *a5 -> r8
void (*a6)(int, char) -> r9
Los sgtes arg van al stack pero del ultimo al primero (der a izq)
int a7 -> pusq (3) (rsp+24)
char a8 -> pusq (2) (rsp+16)
unsigned char a9 -> pusq (1) (rsp+8)
* 
* 
* 
Segun el arg sea signed o unsigned se usara movzbl o movsbl
*/
