#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **AllocateMatrix(int n);
void FreeMatrix(double **matrix, int n);
void AllocateMemory(int n, double **x, double **y, double **delta_x, double **x_exact, double **r, double ***L, double ***A_inv);
void FreeMemory(int n, double **A, double *b, double *x, double *y, double *delta_x, double *x_exact, double *r, double **L, double **A_inv);
#endif