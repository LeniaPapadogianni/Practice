#ifndef LU_DECOMPOSITION_H
#define LU_DECOMPOSITION_H

#include "matrix_operations.h"

// Δηλώσεις συναρτήσεων
void LU_Decomposition(double **A, int n, int **pivot, double **L, double **U);
void Forward_Substitution(double **L, double *b, double *y, int n, int **pivot);
void Backward_Substitution(double **U, double *y, double *x, int n);
void Inverse_LU(double **A, double **A_inv, int n, double **L, double **U, int **pivot, double *y, double *x, double *b);

#endif