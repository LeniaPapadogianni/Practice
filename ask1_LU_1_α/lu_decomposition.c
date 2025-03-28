#include "lu_decomposition.h"

// Υλοποιήσεις συναρτήσεων
void LU_Decomposition(double **A, int n, int **pivot, double **L, double **U) {
    int i, j, k, maxRow;
    double temp;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                L[i][j] = 1;
                pivot[i][j] = 1;
            }
            else {
                L[i][j] = 0;
                pivot[i][j] = 0;
            }
            U[i][j] = A[i][j];
        }
    }

    for (i = 0; i < n; i++) {
        maxRow = i;
        for (j = i + 1; j < n; j++) {
            if (fabs(U[j][i]) > fabs(U[maxRow][i])) {
                maxRow = j;
            }
        }

        if (maxRow != i) {
            for (k = 0; k < n; k++) {
                temp = pivot[i][k];
                pivot[i][k] = pivot[maxRow][k];
                pivot[maxRow][k] = temp;
                temp = U[i][k];
                U[i][k] = U[maxRow][k];
                U[maxRow][k] = temp;
                if (k < i) {
                    temp = L[i][k];
                    L[i][k] = L[maxRow][k];
                    L[maxRow][k] = temp;
                }
            }
        }

        for (j = i+1; j < n; j++) {
            L[j][i] = U[j][i] / U[i][i];
            for (k = i; k < n; k++) {
                U[j][k] -= L[j][i] * U[i][k];
            }
        }
    }
}

void Forward_Substitution(double **L, double *b, double *y, int n, int **pivot) {
    double Pb[n];
    for (int i = 0; i < n; i++) {
        Pb[i] = 0;
        for (int j = 0; j < n; j++) {
            Pb[i] += pivot[i][j] * b[j];
        }
    }
    for (int i = 0; i < n; i++) {
        y[i] = Pb[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }
}

void Backward_Substitution(double **U, double *y, double *x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

void Inverse_LU(double **A, double **A_inv, int n, double **L, double **U, int **pivot, double *y, double *x, double *b) {
    LU_Decomposition(A, n, pivot, L, U);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[j] = 0.0;
        }
        b[i] = 1.0;

        Forward_Substitution(L, b, y, n, pivot);
        Backward_Substitution(U, y, x, n);

        for (int j = 0; j < n; j++) {
            A_inv[j][i] = x[j];
        }
    }
}