#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// printf simplificada: fmt puede tener:
//  i=>integer, c=>char, s=>string
void mini_printf(char *fmt, ...) {
	va_list l;
	int i, ch;
	char c, *s, *p;

	va_start(l, fmt);
	for(p=fmt;*p;p++)
		switch(*p) {
		case 'i': i=va_arg(l, int); printf("%d ",i); break;
		case 's': s=va_arg(l, char *); printf("%s ",s); break;
		case 'c': ch=va_arg(l, int); printf("%c ",ch); break;
		default: abort();
		}
	printf("\n");
	va_end(l);
}

main() {
	mini_printf("iscc", 10, "hola", 'A','z'); 
	mini_printf("sic","uno",9,'c');
}

// No imprime el primer arg...
