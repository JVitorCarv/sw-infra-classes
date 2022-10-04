#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t empty, full;
pthread_mutex_t mutex;
int in = 0, out = 0;
int* buffer;
int N = 0, B = 0, C = 0, P = 0;

void* producer(void* pno);
void* consumer(void* cno);

int main () {
    printf("Inform P, C, B, N: ");
    fflush(stdout);
    scanf("%d %d %d %d", &P, &C, &B, &N);

    pthread_t* pro = (pthread_t*) malloc(sizeof(pthread_t)*P);
    pthread_t* con = (pthread_t*) malloc(sizeof(pthread_t)*C);
    buffer = (int*) malloc(sizeof(int)*B);

    pthread_mutex_init(&mutex, NULL);
    /* First zero represents whether the semaphore will be utilized 
    in different processes or not. In this case, since it will be 
    used in the same process, it is initialized as zero */
    sem_init(&empty, 0, 0);
    sem_init(&full, 0, B);

    int size = P > C ? P : C;
    int* index = (int*) malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++) {
        index[i] = i;
    } 

    for (int i = 0; i < P; i++) {
        pthread_create(&pro[i], NULL, producer, &index[i]);
    }

    for (int i = 0; i < C; i++) {
        pthread_create(&con[i], NULL, consumer, &index[i]);
    }
    for (int i = 0; i < P; i++) pthread_join(pro[i], NULL);
    for (int i = 0; i < C; i++) pthread_join(con[i], NULL);
    
    free(pro);
    free(con);
    free(index);
    free(buffer);
    return 0;
}

void* producer(void* pno) {
    int* id = pno;
    int input;
    while (1) {
        for(int i = 0; i <= N; i++) {
            input = 2*i + 1;
            sem_wait(&full);
                pthread_mutex_lock(&mutex);
                    buffer[in] = input;
                    printf("Producer %d Input %d at index %d\n", *id, input, in);
                    in = (in+1)%B;
                pthread_mutex_unlock(&mutex);
            sem_post(&empty); // sem_signal
        }
    }
}   

void* consumer(void* cno) {
    int *id = cno;
    int output;
    while (1) {
        sem_wait(&empty);
            pthread_mutex_lock(&mutex);
                output = buffer[out];
                printf("Consumer %d Output %d at Index %d\n", *id, output, out);
                out = (out+1)%B;
            pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}