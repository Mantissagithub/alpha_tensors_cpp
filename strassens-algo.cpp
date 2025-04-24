#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

vector<vector<int>> normalMatrixMultiplication(vector<vector<int>> first, vector<vector<int>> second){
    vector<vector<int>> res(2, vector<int>(2));
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            res[i][j] = 0;
            for(int k=0;k<2;k++){
                res[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    return res;
}

int main(){

    cout<<"Enter the matrix of 2 x 2 size: "<<endl;
    
    vector<vector<int>> firstMatrix(2, vector<int>(2));
    vector<vector<int>> secondMatrix(2, vector<int>(2));

    cout<<"ENter the first matrix: "<<endl;

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            int x;
            cout<<"Enter the element at "<<i+1<<" row and "<<j+1<<" column: ";
            cin>>x;
            firstMatrix[i][j] = x;
        }
    }

    cout<<"ENter the second matrix: "<<endl;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            int x;
            cout<<"Enter the element at "<<i+1<<" row and "<<j+1<<" column: ";
            cin>>x;
            secondMatrix[i][j] = x;
        }
    }

    vector<vector<int>> res(2, vector<int>(2));
    vector<vector<int>> normalRes(2, vector<int>(2));

    auto start1 = high_resolution_clock::now();
    normalRes = normalMatrixMultiplication(firstMatrix, secondMatrix);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    cout << "Resultant matrix after normal matrix multiplication: " << endl;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << normalRes[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Time taken for normal matrix multiplication: " << duration1.count() << " microseconds" << endl;

    auto start2 = high_resolution_clock::now();
    res = strassensAlgorithm(firstMatrix, secondMatrix);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << "Resultant matrix after Strassen's algorithm: " << endl;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Time taken for Strassen's algorithm: " << duration2.count() << " microseconds" << endl;

    return 0;
}

// sample output:
// Enter the matrix of 2 x 2 size: 
// ENter the first matrix: 
// Enter the element at 1 row and 1 column: 1
// Enter the element at 1 row and 2 column: 2
// Enter the element at 2 row and 1 column: 3
// Enter the element at 2 row and 2 column: 4
// ENter the second matrix: 
// Enter the element at 1 row and 1 column: 5
// Enter the element at 1 row and 2 column: 6
// Enter the element at 2 row and 1 column: 7
// Enter the element at 2 row and 2 column: 8
// Resultant matrix after normal matrix multiplication: 
// 19 22 
// 43 50 
// Time taken for normal matrix multiplication: 5 microseconds
// Resultant matrix after Strassen's algorithm: 
// 19 22 
// 43 50 
// Time taken for Strassen's algorithm: 4 microseconds