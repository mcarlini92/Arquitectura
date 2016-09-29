.data
.text
f:
	lodsl # eax=(%rsi); rsi+=4
	addl $3, %eax
	stosl # (%rdi)=eax; rdi+=4
/*
void f(int *dst, int *src, int dummy, int len)
{
	int i;
	for(i=0; i<len; i++)
		dst[i] = src[i]+3;
}
*/
