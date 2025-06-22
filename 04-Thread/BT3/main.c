#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int data = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1);

        pthread_mutex_lock(&mutex);

        /* wait until consumer consumed the value of data (data == 0) */
        while (data != 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        data = rand() % 10 + 1;
        printf("Producer: produced %d\n", data);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        /* wait until get new data (data != 0)*/
        while (data == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Consumer: consumed %d\n", data);
        data = 0;  /* reset data after consuming */

        pthread_cond_signal(&cond);  // Báo cho producer biết có thể tạo tiếp
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    int ret;
    pthread_t prod_thread, cons_thread;

    if (ret = pthread_create(&prod_thread, NULL, producer, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&cons_thread, NULL, consumer, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    /* wait until all threads ended */
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
