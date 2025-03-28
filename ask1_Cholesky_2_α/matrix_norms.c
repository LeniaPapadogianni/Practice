#include <math.h>
#include "matrix_norms.h"

double InfinityNorm(double *x, int n) {
    double max = 0.0;
    for (int i = 0; i < n; i++) {
        if (fabs(x[i]) > max) {
            max = fabs(x[i]);
        }
    }
    return max;
}

double cond(double **A, double **A_inv, int n) {
    double norm_A = 0, norm_A_inv = 0;
    
    for (int i = 0; i < n; i++) {
        double row_sum = 0;
        for (int j = 0; j < n; j++) {
            row_sum += fabs(A[i][j]);
        }
        if (row_sum > norm_A) norm_A = row_sum;
    }
    
    for (int i = 0; i < n; i++) {
        double row_sum = 0;
        for (int j = 0; j < n; j++) {
            row_sum += fabs(A_inv[i][j]);
        }
        if (row_sum > norm_A_inv) norm_A_inv = row_sum;
    }
    
    return norm_A * norm_A_inv;
}