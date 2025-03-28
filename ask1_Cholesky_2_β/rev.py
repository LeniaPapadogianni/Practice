import numpy as np

def read_matrix(filename):
    with open(filename, 'r') as file:
        # Διαβάζουμε την πρώτη γραμμή για τη διάσταση
        n = int(file.readline().strip())
        
        # Διαβάζουμε τις υπόλοιπες γραμμές για τα στοιχεία του πίνακα
        matrix = []
        for _ in range(n):
            line = file.readline().strip()
            row = list(map(float, line.split()))
            matrix.append(row)
        
        return np.array(matrix)

def calculate_inverse(matrix):
    try:
        inverse = np.linalg.inv(matrix)
        return inverse
    except np.linalg.LinAlgError:
        print("Ο πίνακας δεν είναι αντιστρέψιμος (ορίζουσα ≈ 0).")
        return None

def main():
    filename = "matrix_100x100.txt"
    
    # Διαβάζουμε τον πίνακα από το αρχείο
    matrix = read_matrix(filename)
    print("Διάσταση πίνακα:", matrix.shape)
    
    # Υπολογίζουμε τον αντίστροφο
    inverse_matrix = calculate_inverse(matrix)
    
    if inverse_matrix is not None:
        print("Ο αντίστροφος πίνακας υπολογίστηκε με επιτυχία!")
        # Μπορείς να εκτυπώσεις μέρος του αντιστρόφου για επαλήθευση (π.χ. τα πρώτα 5x5 στοιχεία)
        print("\nΠρώτα 5x5 στοιχεία του αντιστρόφου:")
        print(inverse_matrix[:5, :5])
        
        # Αποθήκευση του αντιστρόφου σε αρχείο (προαιρετικό)
        np.savetxt("inverse_matrix.txt", inverse_matrix, fmt='%.8f')
        print("\nΟ αντίστροφος αποθηκεύτηκε στο αρχείο 'inverse_matrix.txt'.")

if __name__ == "__main__":
    main()