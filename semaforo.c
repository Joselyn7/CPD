#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0;
int thread_count;
sem_t barrier_sem, count_sem;

void* Thread_work(void* rank) {

    int my_rank = *(int*)rank;

    printf("Hilo %d trabajando antes de la barrera\n", my_rank);

    // Barrera
    sem_wait(&count_sem);
    counter++;
    sem_post(&count_sem);

    if (counter == thread_count) {
        // ultimo hilo en llegar a la barrera despierta a los demas
        sem_post(&barrier_sem);
    }

    // Espera a que todos los hilos lleguen a la barrera
    sem_wait(&barrier_sem);
    sem_post(&barrier_sem);

    // continua con el trabajo
    printf("Hilo %d continua despues de la barrera\n", my_rank);

    return NULL;
}

int main(int argc, char* argv[]) {

    thread_count = atoi(argv[1]);

    // Inicializa los semaforos
    sem_init(&barrier_sem, 0, 0);
    sem_init(&count_sem, 0, 1);

    // Crear hilos
    pthread_t* thread_handles;
    thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < thread_count; i++) {
        int* rank = (int*)malloc(sizeof(int));
        *rank = i;
        pthread_create(&thread_handles[i], NULL, Thread_work, rank);
    }

    // Espera a que todos los hilos terminen
    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }

    free(thread_handles);
    sem_destroy(&barrier_sem);
    sem_destroy(&count_sem);

    return 0;
}

