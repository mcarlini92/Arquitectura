#define N 1024
float a[N];
float b[N]; // Variables globales, van al segmento de datos
				// Asi evito que sean automaticas y vayan al stack
				// Si N es un nro grande, puede arruinar el programa

int main(){
	int i;
	for(i=0; i<N; i++){
		a[i] = i*0.1;
		b[i] = i*0.2;
	}
	struct timespec ini, fin;
	clock_gettime(clock_realtime, &ini);
	clock_gettime(clock_realtime);
	sum(a, b, N);
	clock_gettime(clock_realtime, &fin);
	printf("%ld\n", fin.tv_nsec_ini.tv_nrec); // tv o tu ?
	return 0;
}
