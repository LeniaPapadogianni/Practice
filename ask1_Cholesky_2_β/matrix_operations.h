#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

void PrintMatrix(double **A, int n);
void PrintInvMatrix(double **A, int n);
void Input_Matrix(double ***A, int *n, double **b);
void Random_Matrix(double ***A, int *n, double **b);
void Specific_Matrix(double ***A, int *n, double **b);
void Read_Matrix_From_File(double ***A, int *n, double **b);
void read_inv_matrix(char *filename, double ***matrix, int n);

#endif