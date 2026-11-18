#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX             10000
#define INICIO_CRITICA  4000
#define FIN_CRITICA     6000

sem_t sem_bloqueo; 

void* contar(void* arg) {
    int id = *(int*)arg;

    for (int i = 1; i <= MAX; i++) {
        
        if (i == INICIO_CRITICA)
            sem_wait(&sem_bloqueo);

        printf("Hilo %d: %d\n", id, i);

        if (i == FIN_CRITICA)
            sem_post(&sem_bloqueo);
    }
    return NULL;
}

int main(void) {
    pthread_t h1, h2;
    int id1 = 1, id2 = 2;
    sem_init(&sem_bloqueo, 0, 1);

    pthread_create(&h1, NULL, contar, &id1);
    pthread_create(&h2, NULL, contar, &id2);

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    sem_destroy(&sem_bloqueo);
    return 0;
}
