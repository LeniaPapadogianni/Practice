#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "memory_management.h"
#include "matrix_operations.h"
#include "lu_inverse.h"

int main() {
    int choice, n, **pivot;
    double **A, *b, *x, *y, **L, **U, **A_inv;
    
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

    AllocateMemory(n, &x, &y, &L, &U, &pivot, &A_inv);

    // Υπολογισμός του αντίστροφου πίνακα
    Inverse_LU(A, A_inv, n, L, U, pivot, y, x, b);

    PrintInvMatrix(A_inv, n);

    FreeMemory(n, A, b, x, y, L, U, pivot, A_inv);

    return 0;
}