#ifndef MATRIX_NORMS_H
#define MATRIX_NORMS_H

#include "matrix_operations.h"

// Δηλώσεις συναρτήσεων
double InfinityNorm(double *x, int n);
double cond(double **A, double **A_inv, int n);

#endif