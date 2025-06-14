#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100

int numbers[SIZE];
int even_count = 0;
int odd_count = 0;

void* count_even(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] % 2 == 0)
            even_count++;
    }
    return NULL;
}

void* count_odd(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] % 2 != 0)
            odd_count++;
    }
    return NULL;
}

int main() {
    int ret;
    pthread_t thread1, thread2;

    for (int i = 0; i < SIZE; i++) {
        numbers[i] = i + 1;
    }

    if (ret = pthread_create(&thread1, NULL, count_even, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&thread2, NULL, count_odd, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("The number of even numbers is: %d\n", even_count);
    printf("the number of odd numbers is: %d\n", odd_count);

    return 0;
}
