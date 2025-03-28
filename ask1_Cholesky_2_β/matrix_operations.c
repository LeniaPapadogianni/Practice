#include <time.h>
#include "matrix_operations.h"
#include "memory_management.h"

void PrintMatrix(double **A, int n) {
    printf("Matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2lf ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintInvMatrix(double **A, int n) {
    printf("Inverse of A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4lf ", A[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

// Είσοδος πίνακα από τον χρήστη
void Input_Matrix(double ***A, int *n, double **b) {
    do {
        printf("Give the matrix size n (n x n): ");
        scanf("%d", n);
        if (*n < 2) 
            printf("n must be greater than 1!\n");
    } while (*n < 2);

    *A = AllocateMatrix(*n);  // Δέσμευση μνήμης για τον πίνακα A
    *b = (double *)malloc(*n * sizeof(double));  // Δέσμευση μνήμης για το διάνυσμα b
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("Give the element [%d, %d]:\n", i, j);
            scanf("%lf", &(*A)[i][j]);  // Είσοδος του στοιχείου A[i][j]
            if (i == j) {
                while ((*A)[i][j] <= 0) {
                    printf("Diagonal elements must be positive! Enter again:\n");
                    scanf("%lf", &(*A)[i][j]);  // Επαναφορά εισόδου για θετικό διαγώνιο στοιχείο
                }
            } else {
                (*A)[j][i] = (*A)[i][j];  // Συμμετρία
            }
        }
    }

    // Γέμισμα του διανύσματος b με τυχαίους ακέραιους αριθμούς
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 100;  
    }

    PrintMatrix(*A, *n);
}

void Random_Matrix(double ***A, int *n, double **b) {
    srand(time(NULL));
    *n = rand() % (10 - 2 + 1) + 2;  // Τυχαίο μέγεθος από 2 έως 10

    // Δημιουργία τυχαίου πίνακα C με ακέραια στοιχεία από 1 έως 20
    double **C = AllocateMatrix(*n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            C[i][j] = rand() % 2 + 1;
        }
    }

    // Δημιουργία του θετικά ορισμένου πίνακα A = C^T * C + λI
    *A = AllocateMatrix(*n);
    int lambda = 1;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            (*A)[i][j] = 0;
            for (int k = 0; k < *n; k++) {
                (*A)[i][j] += C[k][i] * C[k][j];  // C^T * C
            }
            if (i == j) {
                (*A)[i][j] += lambda;  // Προσθήκη λI
            }
        }
    }

    // Δημιουργία τυχαίου διανύσματος b με ακέραια στοιχεία από 1 έως 20
    *b = (double *)malloc(*n * sizeof(double));
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 20 + 1;
    }

    PrintMatrix(*A, *n);

    // Απελευθέρωση μνήμης του πίνακα C
    for (int i = 0; i < *n; i++) {
        free(C[i]);
    }
    free(C);
}

void Specific_Matrix(double ***A, int *n, double **b) {
    int choice;
    do {
        printf("Give the matrix size n (n x n): ");
        scanf("%d", n);
        if (*n < 2) 
            printf("n must be greater than 1!\n");
    } while (*n < 2);

    *A = AllocateMatrix(*n);  
    do {
        printf("Choose:\n");
        printf("1. Hilbert matrix\n");
        printf("2. Pascal matrix\n");
        printf("3. Lehmer matrix\n");
        scanf("%d", &choice);
        if (choice == 1) {
            for (int i = 0; i < *n; i++) {
                for (int j = 0; j < *n; j++) {
                    (*A)[i][j] = 1.0 / (i + j + 1);           // Hilbert matrix
                }
            }
        } else if (choice == 2) {                            // Pascal matrix
            for (int i = 0; i < *n; i++) {
                for (int j = 0; j < *n; j++) {
                    if (i == 0 || j == 0) {
                        (*A)[i][j] = 1;
                    } else {
                        (*A)[i][j] = (*A)[i-1][j] + (*A)[i][j-1];
                    }
                }
            }              
        } else if (choice == 3) {                            // Lehmer matrix
            for (int i = 0; i < *n; i++) {
                for (int j = 0; j < *n; j++) {
                    if (i+1 < j+1) {
                        (*A)[i][j] = (double)(i+1) / (j+1);
                    } else {
                        (*A)[i][j] = (double)(j+1) / (i+1);
                    }
                }
            }
        } else {
            printf("Invalid input, try again.\n");
        } 
    } while (choice != 1 && choice != 2 && choice != 3);

    *b = (double *)malloc(*n * sizeof(double));  
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }   
    
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 100;  // Τυχαίοι ακέραιοι από 0 έως 99
    }
    
    PrintMatrix(*A, *n);
}

void Read_Matrix_From_File(double ***A, int *n, double **b) {
    char filename[100];
    printf("Give file's name: ");
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open the file!\n");
        exit(1);
    }

    fscanf(file, "%d", n);  // Διάβασε το μέγεθος του πίνακα
    if (*n < 2) {
        printf("n must be greater than 1!\n");
        exit(1);
    }

    *A = AllocateMatrix(*n);  // Δέσμευση μνήμης για τον πίνακα A
    *b = (double *)malloc(*n * sizeof(double));  // Δέσμευση μνήμης για το διάνυσμα b
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }    

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%lf", &(*A)[i][j]);  // Διάβασε τα στοιχεία του πίνακα
        }
    }

    // Γέμισμα του διανύσματος b με τυχαίους ακέραιους αριθμούς
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 100;  // Τυχαίοι ακέραιοι από 0 έως 99
    }

    fclose(file);

    // Έλεγχος αν ο πίνακας είναι συμμετρικός
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < i; j++) {
            if ((*A)[i][j] != (*A)[j][i]) {
                printf("The matrix is not symmetric!\n");
                exit(1);
            }
        }
    }

    PrintMatrix(*A, *n);
}

void read_inv_matrix(char *filename, double ***matrix, int n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open the file!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf", &(*matrix)[i][j]);
        }
    }
    fclose(file);
}