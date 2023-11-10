#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
int thread_count;
pthread_mutex_t barrier_mutex;
pthread_cond_t barrier_cond;

void* Thread_work(void* rank) {

    int my_rank = *(int*)rank;

    printf("Hilo %d trabajando antes de la barrera\n", my_rank);

    // Barrera
    pthread_mutex_lock(&barrier_mutex);
    counter++;
    if (counter == thread_count) {
        // ultimo hilo en llegar a la barrera, despierta a los demas
        pthread_cond_broadcast(&barrier_cond);
    } else {
        // Hilo no es el ultimo, espera
        pthread_cond_wait(&barrier_cond, &barrier_mutex);
    }
    pthread_mutex_unlock(&barrier_mutex);

    // continua con el trabajo
    printf("Hilo %d continúa después de la barrera\n", my_rank);

    return NULL;
}

int main(int argc, char* argv[]) {
    thread_count = atoi(argv[1]);

    // Inicializa el mutex y la variable de condicion
    pthread_mutex_init(&barrier_mutex, NULL);
    pthread_cond_init(&barrier_cond, NULL);

    // Crear hilos
    pthread_t* thread_handles;
    thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < thread_count; i++) {
        int* rank = (int*)malloc(sizeof(int));
        *rank = i;
        pthread_create(&thread_handles[i], NULL, Thread_work, rank);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }

    free(thread_handles);
    pthread_mutex_destroy(&barrier_mutex);
    pthread_cond_destroy(&barrier_cond);

    return 0;
}

