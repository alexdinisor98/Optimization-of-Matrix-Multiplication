/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"


double* multiply_opt_lowerTrMatrix(int N, double *a, double* b) {
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	register int i = 0, j = 0, k = 0;
	
	for (i = 0; i < N; i++) {
		register double *orig_pa = &a[i * N + 0];
		for (j = 0; j < N; j++) {
			register double *pa = orig_pa + j;
			register double *pb = &b[j * N + j];
			register double sum = 0.0;
			for (k = 0; k < N; k++) {
				sum += *pa * *pb;
				pa++;
				pb += N;
			}
			C[i * N + j] = sum;
		}
	}
	return C;

}

double* multiply_opt_upperTrMatrix(int N, double *a, double* b) {
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	register int i = 0, j = 0, k = 0;
	
	for (i = 0; i < N; i++) {
		register double *orig_pa = &a[i * N + i];
		for (j = 0; j < N; j++) {
			register double *pa = orig_pa;
			register double *pb = &b[i * N + j];
			register double sum = 0.0;
			for (k = i; k < N; k++) {
				sum += *pa * *pb;
				pa++;
				pb += N;
			}
			C[i * N + j] = sum;
		}
	}
	return C;

}


/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	//printf("OPT SOLVER\n");

	double *At = (double *)calloc(N * N, sizeof(double));
	if (At == NULL)
		return NULL;

	double *temp1 = (double *)calloc(N * N, sizeof(double));
	if (temp1 == NULL)
		return NULL;

	double *temp2 = (double *)calloc(N * N, sizeof(double));
	if (temp2 == NULL)
		return NULL;

	double *temp3 = (double *)calloc(N * N, sizeof(double));
	if (temp3 == NULL)
		return NULL;

	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	int idxA = -1;
	int idxAt = -1;
	int i = 0, j = 0;
	int c = 0, d = 0;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (!(i > j)) {
				idxA = i * N + j;
				idxAt = j * N + i;

				At[idxAt] = A[idxA];
			}
		}
	}




	// printf("-------------- A ------------- \n");
	// for (c = 0; c < N; c++) {
	// 	for (d = 0 ; d < N; d++) {
	// 		printf("%f ", A[c * N + d]);
	// 	}
	// 	printf("\n");
	// }

	// printf("-------------- B ------------- \n");

	// for (c = 0; c < N; c++) {
	// 	for (d = 0 ; d < N; d++) {
	// 		printf("%f ", B[c * N + d]);
	// 	}
	// 	printf("\n");
	// }

	//compute B * At
	temp1 = multiply_opt_lowerTrMatrix(N, B, At);
	if (temp1 == NULL)
		return NULL;

	//compute A^2
	temp2 = multiply_opt_upperTrMatrix(N, A, A);
	if (temp2 == NULL)
		return NULL;

	// compute A^2 (=temp2) * B
	temp3 = multiply_opt_upperTrMatrix(N, temp2, B);
	if (temp3 == NULL)
		return NULL;



	// printf("-------------- result ------------- \n");

	//compute sum (B * At + A^2 * B)
	for (c = 0; c < N; c++) {
		for (d = 0 ; d < N; d++) {
			C[c * N + d] = temp1[c * N + d] + temp3[c * N + d];
			// printf("%f ", C[c * N + d]);
		}
		// printf("\n");
	}

	free(At);
	free(temp1);
	free(temp2);
	free(temp3);


	return C;
}
