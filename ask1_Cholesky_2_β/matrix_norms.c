#include <math.h>
#include "matrix_norms.h"

double infinity_norm(double **matrix, int n) {
    double max_norm = 0.0;
    for (int i = 0; i < n; i++) {
        double row_sum = 0.0;
        for (int j = 0; j < n; j++) {
            row_sum += fabs(matrix[i][j]);
        }
        if (row_sum > max_norm) {
            max_norm = row_sum;
        }
    }
    return max_norm;
}