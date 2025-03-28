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

void Input_Matrix(double ***A, int *n, double **b) {
    do {
        printf("Give the matrix size n (n x n): ");
        scanf("%d", n);
        if (*n < 2) 
            printf("n must be greater than 1!\n");
    } while (*n < 2);

    *A = AllocateMatrix(*n);
    *b = (double *)malloc(*n * sizeof(double));
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            printf("Give the element [%d, %d]:\n", i, j);
            scanf("%lf", &(*A)[i][j]);
        }
    }

    // Γέμισμα του διανύσματος b με τυχαίους ακέραιους αριθμούς
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 100;  // Τυχαίοι ακέραιοι από 0 έως 99
    }
    
    PrintMatrix(*A, *n);
}

void Random_Matrix(double ***A, int *n, double **b) {
    srand(time(NULL));
    // Τυχαίο n μεταξύ 2 και 10
    *n = rand() % (10 - 2 + 1) + 2;

    // Δέσμευση μνήμης για τον πίνακα A και το διάνυσμα b
    *A = AllocateMatrix(*n);
    *b = (double *)malloc(*n * sizeof(double));
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Γέμισμα του πίνακα A με τυχαίους ακέραιους αριθμούς
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            (*A)[i][j] = rand() % 100;  // Τυχαίοι ακέραιοι από 0 έως 99
        }
    }
    
    // Γέμισμα του διανύσματος b με τυχαίους ακέραιους αριθμούς
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 100;  // Τυχαίοι ακέραιοι από 0 έως 99
    }

    PrintMatrix(*A, *n);
}

void Specific_Matrix(float ***A, int *n, float **b) {
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
                        (*A)[i][j] = (float)(i+1) / (j+1);
                    } else {
                        (*A)[i][j] = (float)(j+1) / (i+1);
                    }
                }
            }
        } else {
            printf("Invalid input, try again.\n");
        } 
    } while (choice != 1 && choice != 2 && choice != 3);

    *b = (float *)malloc(*n * sizeof(float));  
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
        return;
    }

    fscanf(file, "%d", n);
    if (*n < 2) 
        printf("n must be greater than 1!\n");
        exit(1);

    *A = AllocateMatrix(*n);
    *b = (double *)malloc(*n * sizeof(double));
    if (*b == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%lf", &(*A)[i][j]);
        }
    }

    // Γέμισμα του διανύσματος b με τυχαίους ακέραιους αριθμούς
    for (int i = 0; i < *n; i++) {
        (*b)[i] = rand() % 100;  // Τυχαίοι ακέραιοι από 0 έως 99
    }

    fclose(file);
    PrintMatrix(*A, *n);
}