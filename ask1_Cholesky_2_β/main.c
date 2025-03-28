#include "memory_management.h"
#include "cholesky_inverse.h"
#include "matrix_operations.h"
#include "matrix_norms.h"

int main() {
    int choice, n;
    double **A, **L, *b, *y, *x, **A_inv, **exact_inverse, **difference; 

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

    AllocateMemory(n, &x, &y, &L, &A_inv, &exact_inverse, &difference);

    Inverse_Cholesky(A, n, A_inv, L, y, x);

    PrintInvMatrix(A_inv, n);

    read_inv_matrix("inverse_matrix.txt", &exact_inverse, n);

    // Υπολογισμός διαφοράς D = exact_inverse - approx_inverse
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            difference[i][j] = exact_inverse[i][j] - A_inv[i][j];
        }
    }

    // Υπολογισμός νορμών
    double norm_diff = infinity_norm(difference, n);
    double norm_exact = infinity_norm(exact_inverse, n);
    double relative_error = norm_diff / norm_exact;

    printf("Error = %.4lf\n", relative_error);

    FreeMemory(n, A, b, x, y, L, A_inv, exact_inverse, difference);

    return 0;
}