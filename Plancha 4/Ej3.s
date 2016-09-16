.text
.arm
.global pot
	
pot:
	mov r1, #1			/* r1 = 1*/							
	mov r0, r1, LSL r0 	/* r0 = (1 << r0)*/
	bx lr
	