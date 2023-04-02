#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define SIZE 4

int A[SIZE][SIZE];
int B[SIZE][SIZE];
int C[SIZE][SIZE];

void multiply_matrices_serial(int a[SIZE][SIZE], int b[SIZE][SIZE], int c[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            c[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    struct timeval start, end;
    double parallel_time, serial_time;
    gettimeofday(&start, NULL);
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    printf("Matrix A:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    // Parallel matrix multiplication
    gettimeofday(&start, NULL);
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    parallel_time = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    printf("\nMatrix C (Parallel):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // Serial matrix multiplication
    gettimeofday(&start, NULL);
    multiply_matrices_serial(A, B, C);
    gettimeofday(&end, NULL);
    serial_time = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    printf("\nMatrix C (Serial):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    printf("\nParallel execution time: %f seconds\n", parallel_time);
    printf("Serial execution time: %f seconds\n", serial_time);
    return 0;
}
