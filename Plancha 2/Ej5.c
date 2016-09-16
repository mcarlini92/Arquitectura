#include<stdio.h>
#include<setjmp.h>

int setjmp2(jmp_buf);
int longjmp2(jmp_buf, int);

jmp_buf buf;

int main()
{
    if (setjmp2(buf))
		printf("setjmp no es 0!\n");
    else
    {
        printf("setjmp es 0...\n");
        longjmp2(buf, 21);
    }
    
    return 0;
}
