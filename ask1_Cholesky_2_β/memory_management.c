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

// Αποδέσμευση μνήμης πίνακα
void FreeMatrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void AllocateMemory(int n, double **x, double **y, double ***L, double ***A_inv, double ***exact_inverse, double ***difference) {
    *L = AllocateMatrix(n);
    *A_inv = AllocateMatrix(n);
    *exact_inverse = (double **)malloc(n * sizeof(double *));
    *difference = (double **)malloc(n * sizeof(double *));

    *x = (double *)malloc(n * sizeof(double));
    *y = (double *)malloc(n * sizeof(double));

    if (*x == NULL || *y == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void FreeMemory(int n, double **A, double *b, double *x, double *y, double **L, double **A_inv, double **exact_inverse, double **difference) {
    FreeMatrix(A, n);
    FreeMatrix(L, n);
    FreeMatrix(A_inv, n);
    FreeMatrix(exact_inverse, n);
    FreeMatrix(difference, n);

    free(b);
    free(x);
    free(y);
}