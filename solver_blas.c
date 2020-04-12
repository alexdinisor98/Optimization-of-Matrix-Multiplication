/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
// #include "cblas.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	//printf("BLAS SOLVER\n");
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	
	return NULL;
}
