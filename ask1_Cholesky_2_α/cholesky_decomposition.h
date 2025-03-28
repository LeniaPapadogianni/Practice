#ifndef CHOLESKY_DECOMPOSITION_H
#define CHOLESKY_DECOMPOSITION_H

#include "matrix_operations.h"

void Forward_Substitution(double **L, double *b, double *y, int n);
void Backward_Substitution(double **L, double *y, double *x, int n);
int Cholesky_Decomposition(double **A, int n, double **L);
void Inverse_Cholesky(double **A, int n, double **A_inv, double **L, double *y, double *x);

#endif