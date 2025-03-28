#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memory_management.h"
#include "cholesky_decomposition.h"
#include "matrix_operations.h"
#include "matrix_norms.h"

int main() {
    int choice, n;
    double **A, **L, *b, *y, *x, **A_inv, *x_exact, *delta_x, relative_error, *r, relative_remainder, cpu_time_used;
    clock_t start, end;
    
    do {
        printf("Choose:\n1. Enter data manually\n2. Generate a random matrix\n3. Generate specific matrix\n4. Load a matrix from a file\n");
        scanf("%d", &choice);

        if (choice == 1) 
            Input_Matrix(&A, &n, &b);
        else if (choice == 2) 
            Random_Matrix(&A, &n, &b);
        else if (choice == 3) 
            Specific_Matrix(&A, &n, &b);
        else if (choice == 4)
            Read_Matrix_From_File(&A, &n, &b);
        else    
            printf("Invalid input, try again.\n");
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

    AllocateMemory(n, &x, &y, &delta_x, &x_exact, &r, &L, &A_inv);

    start = clock();

    if (!Cholesky_Decomposition(A, n, L)) {
        FreeMemory(n, A, b, x, y, delta_x, x_exact, r, L, A_inv);
        return 1;
    }
    Forward_Substitution(L, b, y, n);
    Backward_Substitution(L, y, x, n);
        
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (int i = 1; i <= n; i++) 
        printf("x%d = %.2f\n", i, x[i-1]);

    for (int i = 0; i < n; i++) {
        x_exact[i] = (float)(i + 1);
    }

    for (int i = 0; i < n; i++) {
        delta_x[i] = x[i] - x_exact[i];
    }

    relative_error = InfinityNorm(delta_x, n) / InfinityNorm(x_exact, n);

    for (int i = 0; i < n; i++) {
        r[i] = b[i];
        for (int j = 0; j < n; j++) {
            r[i] -= A[i][j] * x[j];
        }
    }

    relative_remainder = InfinityNorm(r, n) / InfinityNorm(b, n);

    Inverse_Cholesky(A, n, A_inv, L, y, x);
    
    float cond_A = cond(A, A_inv, n);
    
    printf("Relative Error: %.6f\n", relative_error);
    printf("Relative Remainder: %.6f\n", relative_remainder);
    printf("Time: %.6f s\n", cpu_time_used);
    printf("Condition number: %.2f\n", cond_A);

    FreeMemory(n, A, b, x, y, delta_x, x_exact, r, L, A_inv);

    return 0;
}