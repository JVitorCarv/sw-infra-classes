#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define EATING 0
#define HUNGRY 1 
#define THINKING 2
#define N 5

int status[N] = {THINKING};
sem_t s[N];
sem_t mutex;

void take_fork(int);
void put_fork(int);
void *phil(void*);

int main() {
    pthread_t threads[N];
    int phil_id[N];
    for (int i = 0; i < N; i++) {
        phil_id[i] = i;
    }

    sem_init(&mutex, 0, 1);

    for(int i = 0; i < N; i++) {
        sem_init(&s[i], 0, 0);
    }

    for(int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, phil, &phil_id[i]);
    }

    for(int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }


    return 0;
}

void *phil(void* id) {
    int* i = id;
    while(1) {
        printf("Philosopher %d is thinking\n", *i);
        sleep(1); // Implementar random
        take_fork(*i);
        sleep(1); // Eating (implementar random)
        put_fork(*i);
    }
}

void take_fork(int id) {
    sem_wait(&mutex);
    if (status[(id + N-1) % N] != EATING && status[(id + 1) % N] != EATING) {
        status[id] = EATING;
        sem_post(&mutex);
    }
    else {
        status[id] = HUNGRY;
        printf("Philosopher %d is hungry\n", id);
        sem_post(&mutex);
        sem_wait(&s[id]); // Está esperando um sinal do semaforo correspondente a ele
    }
    printf("Philosopher %d is eating\n", id);
}

void put_fork(int id) {
    sem_wait(&mutex);
    status[id] = THINKING;
    //Left
    int id_l = (id + N-1) % N;
    if (status[id_l] == HUNGRY) {
        if (status[(id_l + N-1) % N] != EATING) {
            status[id_l] = EATING;
            sem_post(&s[id_l]);
        }
    }
    //Right
    int id_r = (id + 1) % N;
    if (status[id_r] == HUNGRY) {
        if (status[(id_r + 1) % N] != EATING) {
            status[id_r] = EATING;
            sem_post(&s[id_r]);
        }
    }
    sem_post(&mutex);
}