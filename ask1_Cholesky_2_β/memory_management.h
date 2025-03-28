#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **AllocateMatrix(int n);
void FreeMatrix(double **matrix, int n);
void AllocateMemory(int n, double **x, double **y, double ***L, double ***A_inv, double ***exact_inverse, double ***difference);
void FreeMemory(int n, double **A, double *b, double *x, double *y, double **L, double **A_inv, double **exact_inverse, double **difference);

#endif