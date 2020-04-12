/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */

double* multiply(int N, double *first, double* second) {
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	int c = 0, d = 0, k = 0;
	int idx1 = -1;
	int idx2 = -1;
	double sum = 0;

	for (c = 0; c < N; c++) {
			for (d = 0; d < N; d++) {
				for (k = 0; k < N; k++) {
					idx1 = c * N + k;
					idx2 = k * N + d;

					sum += first[idx1] * second[idx2];
				}

				C[c * N + d] = sum;
				sum = 0;
			}
	}

	return C;

}

double* multiply_upperTriangular(int N, double *a) {
	double *C = (double *)calloc(N * N, sizeof(double));
	if (C == NULL)
		return NULL;

	int i = 0, j = 0, k = 0;
	double sum = 0;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				// C is upper triangular as well
				if (!(i > j))
					sum += a[i * N + k] * a[k * N + j];
			}

			C[i * N + j] = sum;
			sum = 0;
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
			idxA = i * N + j;
			idxAt = j * N + i;

			At[idxAt] = A[idxA];
		}
	}

	//compute B * At

	printf("-------------- A ------------- \n");
	for (c = 0; c < N; c++) {
		for (d = 0 ; d < N; d++) {
			printf("%f ", A[c * N + d]);
		}
		printf("\n");
	}

	printf("-------------- B ------------- \n");

	for (c = 0; c < N; c++) {
		for (d = 0 ; d < N; d++) {
			printf("%f ", B[c * N + d]);
		}
		printf("\n");
	}

	temp1 = multiply(N, B, At);
	if (temp1 == NULL)
		return NULL;

	//compute A^2
	temp2 = multiply_upperTriangular(N, A);
	if (temp2 == NULL)
		return NULL;

	// compute A^2 (=temp2) * B
	temp3 = multiply(N, temp2, B);
	if (temp3 == NULL)
		return NULL;



	printf("-------------- result ------------- \n");

	// compute sum (B * At + A^2 * B)
	for (c = 0; c < N; c++) {
		for (d = 0 ; d < N; d++) {
			C[c * N + d] = temp1[c * N + d] + temp3[c * N + d];
			printf("%f ", C[c * N + d]);
		}
		printf("\n");
	}

	free(At);
	free(temp1);
	free(temp2);
	free(temp3);


	return C;
}
