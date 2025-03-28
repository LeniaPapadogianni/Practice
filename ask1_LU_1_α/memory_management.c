#include <time.h>
#include "memory_management.h"

float **AllocateMatrix(int n) {
    float **matrix = (float **)malloc(n * sizeof(float *));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (float *)malloc(n * sizeof(float));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    return matrix;
}

void FreeMatrix(float **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int **AllocatePivot(int n) {
    int **pivot = (int **)malloc(n * sizeof(int *));
    if (pivot == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        pivot[i] = (int *)malloc(n * sizeof(int));
        if (pivot[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    return pivot;
}

void FreePivot(int **pivot, int n) {
    for (int i = 0; i < n; i++) {
        free(pivot[i]);
    }
    free(pivot);
}

void AllocateMemory(int n, double **x, double **y, double **delta_x, double **x_exact, double **r, double ***L, double ***U, int ***pivot, double ***A_inv) {
    *L = AllocateMatrix(n);
    *U = AllocateMatrix(n);
    *pivot = AllocatePivot(n);
    *A_inv = AllocateMatrix(n);

    *x = (double *)malloc(n * sizeof(double));
    *y = (double *)malloc(n * sizeof(double));
    *delta_x = (double *)malloc(n * sizeof(double));
    *x_exact = (double *)malloc(n * sizeof(double));
    *r = (double *)malloc(n * sizeof(double));

    if (*x == NULL || *y == NULL || *delta_x == NULL || *x_exact == NULL || *r == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void FreeMemory(int n, double **A, double *b, double *x, double *y, double *delta_x, double *x_exact, double *r, double **L, double **U, int **pivot, double **A_inv) {
    FreeMatrix(A, n);
    FreeMatrix(L, n);
    FreeMatrix(U, n);
    FreePivot(pivot, n);
    FreeMatrix(A_inv, n);

    free(b);
    free(x);
    free(y);
    free(delta_x);
    free(x_exact);
    free(r);
}