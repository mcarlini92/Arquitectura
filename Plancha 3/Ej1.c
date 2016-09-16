#include <stdio.h>

#define MANTISA(x)  (0x7fffff & *((int *)&(x)))
#define EXPONENTE(x)  (0xff & (*((int *)&(x)) >> 23))
#define SIGNO(x)  (*((int *)&(x)) >> 31)

int main()
{
  float f = 6.02252e23;
  printf("Signo: %s/nExponente: %d/nMantisa: %d\n", f, (SIGNO(f) ? "-" : "+"), EXPONENTE(f), MANTISA(f));
  return 0;
  }

 /*
  1    8               23              <-- Tamaño en bits
 +-+--------+-----------------------+
 |S|  Exp   |  Mantisa              |
 +-+--------+-----------------------+
 31 30    23 22                    0   <-- Indice del bit (0 a la derecha)
	
/*