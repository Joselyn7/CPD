#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
int thread_count;
pthread_mutex_t barrier_mutex;

void* Thread_work(void* rank) {

    int my_rank = *(int*)rank;
    
    printf("Hilo %d trabajando antes de la barrera\n", my_rank);

    // Barrera
    pthread_mutex_lock(&barrier_mutex);
    counter++;
    pthread_mutex_unlock(&barrier_mutex);
    printf("Hilo %d ha llegado a la barrera\n", my_rank);

    while (counter < thread_count);

    // continua con el trabajo
    printf("Hilo %d continua despues de la barrera\n", my_rank);

    return NULL;
}

int main(int argc, char* argv[]) {

    thread_count = atoi(argv[1]);
    pthread_mutex_init(&barrier_mutex, NULL);

    pthread_t* thread_handles;
    thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    
    for (int i = 0; i < thread_count; i++) {
        int* rank = (int*)malloc(sizeof(int));
        *rank = i;
        pthread_create(&thread_handles[i], NULL, Thread_work, rank);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }

    free(thread_handles);
    pthread_mutex_destroy(&barrier_mutex);

    return 0;
}
