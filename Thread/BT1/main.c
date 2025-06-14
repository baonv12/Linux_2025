#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

static void *thr_handle(void *args) 
{
    pthread_t tid = pthread_self();

    if (pthread_equal(tid, thread_id1)) {
        printf("I'm thread_id1, my tid is %ld\n", (unsigned long)tid);
    } else {
        printf("I'm thread_id2, my tid is %ld\n", (unsigned long)tid);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int ret;

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(1);

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    printf("All threads have finished.\n");

    return 0;
}