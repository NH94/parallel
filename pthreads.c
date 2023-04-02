#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ms 10
#define threadn 4

int matrix_a[ms][ms];
int matrix_b[ms][ms];
int matrix_c[ms][ms];

int step_i = 0;


void* multiply(void* arg) {
    int i;
    while (1) {
        i = step_i;
        step_i++;
        if (i >= ms) {
            break;
        }
        for (int j = 0; j < ms; j++) {
            matrix_c[i][j] = 0;
            for (int k = 0; k < ms; k++) {
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    struct timeval start_time, end_time, serial_start_time, serial_end_time;
    gettimeofday(&start_time, NULL);

    srand(time(NULL));
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < ms; j++) {
            matrix_a[i][j] = rand() % 10;
            matrix_b[i][j] = rand() % 10;
        }
    }

    printf("Matrix A:\n");
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < ms; j++) {
            printf("%d ", matrix_a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < ms; j++) {
            printf("%d ", matrix_b[i][j]);
        }
        printf("\n");
    }

    gettimeofday(&serial_start_time, NULL);
    // Serial Matrix Multiplication
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < ms; j++) {
            matrix_c[i][j] = 0;
            for (int k = 0; k < ms; k++) {
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    gettimeofday(&serial_end_time, NULL);

    pthread_t threads[threadn];
    for (int i = 0; i < threadn; i++) {
        pthread_create(&threads[i], NULL, multiply, NULL);
    }

    for (int i = 0; i < threadn; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);
    double parallel_elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1000000u + end_time.tv_usec - start_time.tv_usec) / 1.e6;
    double serial_elapsed_time = ((serial_end_time.tv_sec - serial_start_time.tv_sec) * 1000000u + serial_end_time.tv_usec - serial_start_time.tv_usec) / 1.e6;

    printf("\nMatrix C (Parallel):\n");
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < ms; j++) {
            printf("%d ", matrix_c[i][j]);
        }
        printf("\n");
    }
    printf("Serial execution time %f seconds\n",serial_elapsed_time);
    printf("\nParallel Execution time with %d threads: %f seconds",threadn,parallel_elapsed_time);
    return 0;
}
