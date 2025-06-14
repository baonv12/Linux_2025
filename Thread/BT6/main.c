#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000000
#define NUM_THREADS 4

int array[SIZE];
int global_sum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
} ThreadData;

void* partial_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long local_sum = 0;

    for (int i = data->start; i < data->end; i++) {
        local_sum += array[i];
    }

    pthread_mutex_lock(&lock);
    global_sum += local_sum;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    /* Assign 1 to all elements of array, so expected sum of array is 1000000 */
    for (int i = 0; i < SIZE; i++) {
        array[i] = 1;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int chunk_size = SIZE / NUM_THREADS;

    /* Create 4 threads and devide into 4 ranges for each thread to process */
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, partial_sum, &thread_data[i]);
    }

    /* wait until all thread ended */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Sum of array: %d\n", global_sum);
    return 0;
}
