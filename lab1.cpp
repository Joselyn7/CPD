#include <iostream>
#include <ctime> 

const int MAX = 1000;

int main() {
    double A[MAX][MAX];
    double x[MAX];
    double y[MAX];

    // Declaración de variables de tiempo para el primer par de bucles
    clock_t start, end;
    double cpu_time_used;

    // Inicializa A, x y asigna y = 0
    for (int i = 0; i < MAX; i++) {
        x[i] = 1.0; 
        y[i] = 0.0;
        for (int j = 0; j < MAX; j++) {
            A[i][j] = 1.0;
        }
    }

    // Medir el tiempo para el primer par de bucles (acceso contiguo)
    start = clock();

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    std::cout << "Tiempo para el primer par de bucles: " << cpu_time_used << " segundos" << std::endl;


    return 0;
}
