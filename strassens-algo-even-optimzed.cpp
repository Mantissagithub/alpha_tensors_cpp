#include <bits/stdc++.h>
using namespace std;
using Matrix = vector<vector<int>>;

Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix sub(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

void normalMultiply(const Matrix &A, const Matrix &B, Matrix &C) {
    int n = A.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void strassen(const Matrix &A, const Matrix &B, Matrix &C, int threshold) {
    int n = A.size();
    if (n <= threshold) {
        normalMultiply(A, B, C);
        return;
    }

    int k = n / 2;
    Matrix A11(k, vector<int>(k)), A12(k, vector<int>(k)),
           A21(k, vector<int>(k)), A22(k, vector<int>(k));
    Matrix B11(k, vector<int>(k)), B12(k, vector<int>(k)),
           B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    Matrix M1(k, vector<int>(k)), M2(k, vector<int>(k)),
           M3(k, vector<int>(k)), M4(k, vector<int>(k)),
           M5(k, vector<int>(k)), M6(k, vector<int>(k)), M7(k, vector<int>(k));

    strassen(add(A11, A22), add(B11, B22), M1, threshold);
    strassen(add(A21, A22), B11, M2, threshold);
    strassen(A11, sub(B12, B22), M3, threshold);
    strassen(A22, sub(B21, B11), M4, threshold);
    strassen(add(A11, A12), B22, M5, threshold);
    strassen(sub(A21, A11), add(B11, B12), M6, threshold);
    strassen(sub(A12, A22), add(B21, B22), M7, threshold);

    Matrix C11 = add(sub(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(sub(add(M1, M3), M2), M6);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
}

int main() {
    cout << "Strassen's algorithm for even matrices (2^n x 2^n)\n";
    int n;
    cout << "Enter the size of the matrix (2^n): ";
    cin >> n;
    Matrix A(n, vector<int>(n)), B(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    Matrix C1(n, vector<int>(n)), C2(n, vector<int>(n));

    auto start = chrono::high_resolution_clock::now();
    normalMultiply(A, B, C1);
    auto end = chrono::high_resolution_clock::now();
    auto normal_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    strassen(A, B, C2, 64);
    end = chrono::high_resolution_clock::now();
    auto strassen_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    bool equal = true;
    for (int i = 0; i < n && equal; i++)
        for (int j = 0; j < n && equal; j++)
            if (C1[i][j] != C2[i][j])
                equal = false;

    cout << "Time taken by normal multiplication: " << normal_time << " microseconds\n";
    cout << "Time taken by Strassen's algorithm: " << strassen_time << " microseconds\n";
    cout << "Speedup: " << (double)normal_time / strassen_time << " times\n";
    cout << (equal ? "Both results are equal.\n" : "Mismatch in results.\n");
    return 0;
}

// sample output:
// pradhep@mantis:~/alpha_tensors_cpp$ g++ strassens-algo-even-optimzed.cpp -o strassens-algo-even-optimzed
// pradhep@mantis:~/alpha_tensors_cpp$ ./strassens-algo-even-optimzed 
// Strassen's algorithm for even matrices (2^n x 2^n)
// Enter the size of the matrix (2^n): 64
// Time taken by normal multiplication: 4263 microseconds
// Time taken by Strassen's algorithm: 3678 microseconds
// Speedup: 1.15905 times
// Both results are equal.
// pradhep@mantis:~/alpha_tensors_cpp$ ./strassens-algo-even-optimzed 
// Strassen's algorithm for even matrices (2^n x 2^n)
// Enter the size of the matrix (2^n): 128
// Time taken by normal multiplication: 29978 microseconds
// Time taken by Strassen's algorithm: 12864 microseconds
// Speedup: 2.33038 times
// Both results are equal.
// pradhep@mantis:~/alpha_tensors_cpp$ 
