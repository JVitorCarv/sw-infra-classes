#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int size;
    int *values;
}datastruct;

void *avg_func(void *str);
void *min_func(void *str);
double avg = 0;
int min;

int main(int argc, char *argv[]) {
    int i;

    while (argc <= 1) {
        printf("No arguments entered\n");
        exit(0);
    }

    int copy[argc-1]; //-1 because a.out is also counted as an argument
    for (i = 0; i < (argc - 1); i++) {
        copy[i] = atoi(argv[i+1]);
        //copy[i] = (int) argv[i+1]; this should not be used as casting only works properly on a single char and uses ASCII values
    }

    datastruct ds = {argc - 1, copy};

    pthread_t thread1, thread2, thread3;
    int t1, t2;

    t1 = pthread_create(&thread1, NULL, (void *) avg_func, (void *) &ds);
    if (t1) {
        fprintf(stderr, "Error pthread with code %d\n", t1);
        exit(EXIT_FAILURE);
    }

    t2 = pthread_create(&thread2, NULL, (void *) min_func, (void *) &ds);
    if (t2) {
        fprintf(stderr, "Error pthread with code %d", t2);
        exit(EXIT_FAILURE);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("The average: %g\n", avg);
    printf("The minimum: %d\n", min);

    exit(EXIT_SUCCESS);
}

void *avg_func(void *ptr) {
    datastruct *data;
    data = (datastruct *) ptr;

    int sz = data->size;
    for (int i = 0; i < sz; i++) {
        avg += (data->values[i]);
    }

    avg = avg/sz;
}

void *min_func(void *ptr) {
    datastruct *data;
    data = (datastruct *) ptr;

    int sz = data->size;

    min = data->values[0];
    for (int i = 0; i < sz; i++) {
        if (data->values[i] < min) {
            min = data->values[i];
        }
    }
}