#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int data = 0;
pthread_rwlock_t rwlock;

void* reader(void* arg) {
    int id = *((int*)arg);
    sleep(1); 

    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %d: reading data = %d\n", id, data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);

    printf("Reader %d: finished reading\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    sleep(1);

    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("Writer %d: incremented data to %d\n", id, data);
    sleep(1); 
    pthread_rwlock_unlock(&rwlock);

    printf("Writer %d: finished writing\n", id);
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int ids[NUM_READERS > NUM_WRITERS ? NUM_READERS : NUM_WRITERS];

    pthread_rwlock_init(&rwlock, NULL);

    /* create reader threads */ 
    for (int i = 0; i < NUM_READERS; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    /* create writer threads */ 
    for (int i = 0; i < NUM_WRITERS; i++) {
        ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    /* wait until all thread ended */
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    printf("Final value of data: %d\n", data);
    return 0;
}
