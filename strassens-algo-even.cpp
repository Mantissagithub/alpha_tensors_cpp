#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

vector<vector<int>> subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

vector<vector<int>> getQuadrant(vector<vector<int>>& matrix, int row, int col, int size) {
    vector<vector<int>> quadrant(size, vector<int>(size));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            quadrant[i][j] = matrix[i + row][j + col];
    return quadrant;
}

void combineQuadrants(vector<vector<int>>& result, vector<vector<int>>& C11, 
                     vector<vector<int>>& C12, vector<vector<int>>& C21, 
                     vector<vector<int>>& C22, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            result[i][j] = C11[i][j];
            result[i][j + size] = C12[i][j];
            result[i + size][j] = C21[i][j];
            result[i + size][j + size] = C22[i][j];
        }
    }
}

vector<vector<int>> strassensAlgorithm(vector<vector<int>> first, vector<vector<int>> second){
    int m1 = (first[0][0] + first[1][1]) * (second[0][0] + second[1][1]);
    int m2 = (first[1][0] + first[1][1])* second[0][0];
    int m3 = first[0][0] * (second[0][1] - second[1][1]);
    int m4 = first[1][1]* (second[1][0] - second[0][0]);
    int m5 = (first[0][0] + first[0][1]) * second[1][1];
    int m6 = (first[1][0] - first[0][0]) * (second[0][0] + second[0][1]);
    int m7  = (first[0][1] - first[1][1]) * (second[1][0] + second[1][1]);

    vector<vector<int>> res(2, vector<int>(2));
    res[0][0] = m1 + m4 - m5 + m7;
    res[0][1] = m3 + m5;
    res[1][0] = m2 + m4;
    res[1][1] = m1 - m2 + m3 + m6;

    return res;
}

vector<vector<int>> strassenMultiply(vector<vector<int>>& A, vector<vector<int>>& B, int n) {
    if(n == 2){
        return strassensAlgorithm(A, B);
    }
    int newSize = n/2;
    
    vector<vector<int>> A11 = getQuadrant(A, 0, 0, newSize);
    vector<vector<int>> A12 = getQuadrant(A, 0, newSize, newSize);
    vector<vector<int>> A21 = getQuadrant(A, newSize, 0, newSize);
    vector<vector<int>> A22 = getQuadrant(A, newSize, newSize, newSize);
    
    vector<vector<int>> B11 = getQuadrant(B, 0, 0, newSize);
    vector<vector<int>> B12 = getQuadrant(B, 0, newSize, newSize);
    vector<vector<int>> B21 = getQuadrant(B, newSize, 0, newSize);
    vector<vector<int>> B22 = getQuadrant(B, newSize, newSize, newSize);

    auto temp1 = addMatrix(A11, A22, newSize);
    auto temp2 = addMatrix(B11, B22, newSize);
    vector<vector<int>> M1 = strassenMultiply(temp1, temp2, newSize);

    temp1 = addMatrix(A21, A22, newSize);
    vector<vector<int>> M2 = strassenMultiply(temp1, B11, newSize);

    temp1 = subtractMatrix(B12, B22, newSize);
    vector<vector<int>> M3 = strassenMultiply(A11, temp1, newSize);

    temp1 = subtractMatrix(B21, B11, newSize);
    vector<vector<int>> M4 = strassenMultiply(A22, temp1, newSize);

    temp1 = addMatrix(A11, A12, newSize);
    vector<vector<int>> M5 = strassenMultiply(temp1, B22, newSize);

    temp1 = subtractMatrix(A21, A11, newSize);
    temp2 = addMatrix(B11, B12, newSize);
    vector<vector<int>> M6 = strassenMultiply(temp1, temp2, newSize);

    temp1 = subtractMatrix(A12, A22, newSize);
    temp2 = addMatrix(B21, B22, newSize);
    vector<vector<int>> M7 = strassenMultiply(temp1, temp2, newSize);

    auto C11 = addMatrix(subtractMatrix(addMatrix(M1, M4, newSize), M5, newSize), M7, newSize);
    auto C12 = addMatrix(M3, M5, newSize);
    auto C21 = addMatrix(M2, M4, newSize);
    auto C22 = addMatrix(subtractMatrix(addMatrix(M1, M3, newSize), M2, newSize), M6, newSize);

    vector<vector<int>> result(n, vector<int>(n));
    combineQuadrants(result, C11, C12, C21, C22, newSize);
    
    return result;
}

vector<vector<int>> normalMultiply(vector<vector<int>>& A, vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            for(int k = 0; k < size; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main(){
    cout<<"Strassen's algorithm for even matrices (2^n x 2^n)"<<endl;

    cout<<"Enter the size of the matrix (2^n): ";
    int n;
    cin>>n;
    int m = pow(2, n);

    vector<vector<int>> firstMatrix(m, vector<int>(m));
    vector<vector<int>> secondMatrix(m, vector<int>(m));

    // cout<<"Enter the first matrix: "<<endl;
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<m;j++){
    //         int x;
    //         cout<<"Enter the element at "<<i+1<<" row and "<<j+1<<" column: ";
    //         cin>>x;
    //         firstMatrix[i][j] = x;
    //     }
    // }

    // cout<<"Enter the second matrix: "<<endl;
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<m;j++){
    //         int x;
    //         cout<<"Enter the element at "<<i+1<<" row and "<<j+1<<" column: ";
    //         cin>>x;
    //         secondMatrix[i][j] = x;
    //     }
    // }

    srand(time(0));
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            firstMatrix[i][j] = rand() % 100;

    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            secondMatrix[i][j] = rand() % 100;


    auto start1 = high_resolution_clock::now();
    vector<vector<int>> normalResult = normalMultiply(firstMatrix, secondMatrix, m);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    auto start2 = high_resolution_clock::now();
    vector<vector<int>> strassenResult = strassenMultiply(firstMatrix, secondMatrix, m);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    // cout << "\nNormal Multiplication Result:" << endl;
    // for(int i = 0; i < m; i++) {
    //     for(int j = 0; j < m; j++)
    //         cout << normalResult[i][j] << " ";
    //     cout << endl;
    // }
    cout << "Time taken by normal multiplication: " << duration1.count() << " microseconds" << endl;

    // cout << "\nStrassen's Algorithm Result:" << endl;
    // for(int i = 0; i < m; i++) {
    //     for(int j = 0; j < m; j++)
    //         cout << strassenResult[i][j] << " ";
    //     cout << endl;
    // }
    cout << "Time taken by Strassen's algorithm: " << duration2.count() << " microseconds" << endl;

    cout << "Speedup: " << (double)duration1.count() / duration2.count() << " times" << endl;

    if(normalResult == strassenResult)
            cout << "Both results are equal." << endl;
        else
            cout << "Results are not equal." << endl;

    return 0;
}