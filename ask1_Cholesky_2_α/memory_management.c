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

void AllocateMemory(int n, double **x, double **y, double **delta_x, double **x_exact, double **r, double ***L, double ***A_inv) {
    *L = AllocateMatrix(n);
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

void FreeMemory(int n, double **A, double *b, double *x, double *y, double *delta_x, double *x_exact, double *r, double **L, double **A_inv) {
    FreeMatrix(A, n);
    FreeMatrix(L, n);
    FreeMatrix(A_inv, n);

    free(b);
    free(x);
    free(y);
    free(delta_x);
    free(x_exact);
    free(r);
}