/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */

double* multiply_withLowerTrMatrix(int N, double *first, double* second) {
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	int c = 0, d = 0, k = 0;

	for (c = 0; c < N; c++) {
		for (d = 0; d < N; d++) {
			for (k = d; k < N; k++) {
				C[c * N + d] += first[c * N + k] * second[k * N + d];
			}

		}
	}

	return C;

}

double* multiply_withUpperTrMatrix(int N, double *first, double* second) {
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	int c = 0, d = 0, k = 0;

	for (c = 0; c < N; c++) {
		for (d = 0; d < N; d++) {
			for (k = c; k < N; k++) {
				C[c * N + d] += first[c * N + k] * second[k * N + d];
			}
		}
	}

	return C;

}

double* my_solver(int N, double *A, double* B) {
	//printf("NEOPT SOLVER\n");
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
	temp1 = multiply_withLowerTrMatrix(N, B, At);
	if (temp1 == NULL)
		return NULL;

	//compute A^2
	temp2 = multiply_withUpperTrMatrix(N, A, A);
	if (temp2 == NULL)
		return NULL;

	// compute A^2 (=temp2) * B
	temp3 = multiply_withUpperTrMatrix(N, temp2, B);
	if (temp3 == NULL)
		return NULL;



	//printf("-------------- result ------------- \n");

	// compute sum (B * At + A^2 * B)
	for (c = 0; c < N; c++) {
		for (d = 0 ; d < N; d++) {
			C[c * N + d] = temp1[c * N + d] + temp3[c * N + d];
			//printf("%f ", C[c * N + d]);
		}
		//printf("\n");
	}

	free(At);
	free(temp1);
	free(temp2);
	free(temp3);


	return C;
}
