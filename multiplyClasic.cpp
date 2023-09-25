#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    std::vector<std::vector<int>> result(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

int main() {
    
    int size1 = 500;
    int size2 = 500;
    int size3 = 500;

    
    std::vector<std::vector<int>> A(size1, std::vector<int>(size2, 2));
    std::vector<std::vector<int>> B(size2, std::vector<int>(size3, 3));

    //print
    /*
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> result = multiplyMatrices(A, B);
    auto end = std::chrono::high_resolution_clock::now();

    //print
    /*
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size3; ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */ 
    
    std::chrono::duration<double> duration = end - start;
    double milliseconds = duration.count() * 1000;

    // Tiempo de ejecución
    std::cout << "Tiempo de ejecución: " << milliseconds << " ms" << std::endl;

    return 0;
}
