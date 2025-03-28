#include <stdio.h>
#include <math.h>
#include "cholesky_inverse.h"
#include "memory_management.h"

// Επίλυση Ly = b (Forward Substitution)
void Forward_Substitution(double **L, double *b, double *y, int n) {
    // Υπολογισμός του y
    for (int i = 0; i < n; i++) {
        y[i] = b[i];  // Αρχικοποίηση του y[i] με b[i]
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];  // Αφαίρεση των γνωστών όρων
        }
        y[i] /= L[i][i];  // Διαίρεση με το διαγώνιο στοιχείο (αν δεν είναι 1)
    }

    // Εκτύπωση του y
    // for (int i = 0; i < n; i++) 
    //     printf("y[%d] = %.2f\n", i, y[i]);
}

// Επίλυση L^T x = y (Backward Substitution)
void Backward_Substitution(double **L, double *y, double *x, int n) {
    // Εύρεση του ανάστροφου L^T
    double **L_T;
    L_T = AllocateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L_T[i][j] = L[j][i];
        }
    } 
    // Υπολογισμός του x
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];  // Αρχικοποίηση του x[i] με την τιμή του y[i]
        for (int j = i + 1; j < n; j++) {
            x[i] -= L_T[i][j] * x[j];  // Αφαίρεση των γνωστών όρων
        }
        x[i] /= L_T[i][i];  // Κανονικοποίηση με το διαγώνιο στοιχείο
    }
    FreeMatrix(L_T, n);
}

int Cholesky_Decomposition(double **A, int n, double **L) {
    int i, j, k;

    // Αρχικοποίηση του L με μηδενικά
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            L[i][j] = 0;
        }
    }

    // Υπολογισμός του L
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            double sum = 0;

            if (i == j) {  // Διαγώνια στοιχεία
                for (k = 0; k < j; k++) {
                    sum += L[j][k] * L[j][k];
                }
                if (A[j][j] - sum <= 0) {
                    printf("The matrix is not positive definite! Cholesky Decomposition failed\n");
                    exit(1);  // Ο πίνακας δεν είναι θετικά ορισμένος
                }
                L[j][j] = sqrt(A[j][j] - sum);
            } else {  // Μη διαγώνια στοιχεία
                for (k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    // printf("Matrix L:\n");
    // PrintMatrix(L, n);
    return 1;  // Επιτυχής διάσπαση
}

void Inverse_Cholesky(double **A, int n, double **A_inv, double **L, double *y, double *x) {
    double *e;

    e = (double *)malloc(n * sizeof(double));
    if (e == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    if (!Cholesky_Decomposition(A, n, L)) {
        printf("Cholesky decomposition failed. Cannot compute inverse.\n");
        return;
    }

    for (int j = 0; j < n; j++) {
        // Δημιουργία της j-οστής στήλης του μοναδιαίου πίνακα
        for (int i = 0; i < n; i++) {
            e[i] = (i == j) ? 1.0 : 0.0;
        }

        // Επίλυση Ly = e
        Forward_Substitution(L, e, y, n);

        // Επίλυση L^T x = y
        Backward_Substitution(L, y, x, n);

        // Αποθήκευση της λύσης ως στήλη του A_inv
        for (int i = 0; i < n; i++) {
            A_inv[i][j] = x[i];
        }
    }

    free(e);
}