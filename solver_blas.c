/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
        //printf("BLAS SOLVER\n");
        int c = 0, d = 0, i = 0;
        double *C = (double *)calloc(N * N, sizeof(double));
        if (C == NULL)
                return NULL;

        double *tempA = (double *)calloc(N * N, sizeof(double));
        if (tempA == NULL)
                return NULL;

        for(i = 0; i < N * N; i++)
                tempA[i] = A[i];

        double *tempB = (double *)calloc(N * N, sizeof(double));
        if (tempB == NULL)
                return NULL;

        for(i = 0; i < N * N; i++)
                tempB[i] = B[i];

        //compute B * At
        cblas_dtrmm(CblasRowMajor, CblasRight,
                CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, B, N);

        // compute A ^ 2
        cblas_dtrmm(CblasRowMajor, CblasLeft,
                CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, tempA, N);

        // compute A^2 * B
        cblas_dtrmm(CblasRowMajor, CblasLeft,
                CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, tempA, N, tempB, N);


        for (c = 0; c < N; c++) {
                for (d = 0 ; d < N; d++) {
                        C[c * N + d] = B[c * N + d] + tempB[c * N + d];
                }
        }

        free(tempA);
        free(tempB);

        return C;
}
