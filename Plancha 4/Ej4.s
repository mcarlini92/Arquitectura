.text
.arm
.global det
/* La matriz es de la forma */
/* s0 s1 */
/* s2 s3*/
/* Se debe devolver s0*s3 - s2*s1 */

det:
	fmuls s0, s0, s3	/* s0 = a * b */
	fmuls s1, s1, s2	/* s1 = c * d */
	fsubs s0, s0, s1	/* s0 = (a*b)-(b*c) */
	
	bx lr

	

