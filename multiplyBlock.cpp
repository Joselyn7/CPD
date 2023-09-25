#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::vector<int>> multiplyMatricesBlock(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int blockSize) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    std::vector<std::vector<int>> result(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; i += blockSize) {
        for (int j = 0; j < colsB; j += blockSize) {
            for (int k = 0; k < colsA; k += blockSize) {
                for (int ii = i; ii < std::min(i + blockSize, rowsA); ++ii) {
                    for (int jj = j; jj < std::min(j + blockSize, colsB); ++jj) {
                        for (int kk = k; kk < std::min(k + blockSize, colsA); ++kk) {
                            result[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    
    int size1 = 500;
    int size2 = 500;
    int size3 = 500;
    int blockSize = 256;  // Tamaño del bloque
    
    std::vector<std::vector<int>> A(size1, std::vector<int>(size2, 2));
    std::vector<std::vector<int>> B(size2, std::vector<int>(size3, 3));

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> result = multiplyMatricesBlock(A, B, blockSize);
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
    std::cout << "Tiempo de ejecución (por bloques): " << milliseconds << " ms" << std::endl;

    return 0;
}
