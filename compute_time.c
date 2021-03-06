#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval start, stop;
unsigned diffsec, diffusec;

void compute_time_and_flush();

void time_log_start() {
	gettimeofday(&start, NULL);
}

void time_log_stop() {
	gettimeofday(&stop, NULL);
	compute_time_and_flush();
}

void compute_time_and_flush() {
		diffsec = stop.tv_sec - start.tv_sec;
		diffusec = (stop.tv_usec - start.tv_usec) >= 0 ? (stop.tv_usec - start.tv_usec) : 1000000 - stop.tv_usec;
		
		printf("%d,%d\n", diffsec, diffusec);	
}
