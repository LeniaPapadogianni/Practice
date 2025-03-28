#include <time.h>
#include "memory_management.h"

double **AllocateMatrix(int n) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    return matrix;
}

void FreeMatrix(double **matrix, int n) {
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

void AllocateMemory(int n, double **x, double **y, double ***L, double ***U, int ***pivot, double ***A_inv) {
    *L = AllocateMatrix(n);
    *U = AllocateMatrix(n);
    *pivot = AllocatePivot(n);
    *A_inv = AllocateMatrix(n);

    *x = (double *)malloc(n * sizeof(double));
    *y = (double *)malloc(n * sizeof(double));

    if (*x == NULL || *y == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void FreeMemory(int n, double **A, double *b, double *x, double *y, double **L, double **U, int **pivot, double **A_inv) {
    FreeMatrix(A, n);
    FreeMatrix(L, n);
    FreeMatrix(U, n);
    FreePivot(pivot, n);
    FreeMatrix(A_inv, n);

    free(b);
    free(x);
    free(y);
}