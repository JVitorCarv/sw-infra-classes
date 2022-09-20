#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
void *avg_func(void *str);
void *min_func(void *ptr);
void *max_func(void *ptr);

double avg;        
int min;
int max;

typedef struct
{
    int size;
    int * values;
}datastruct;

void main(int argc, char *argv[])
{
    while(argc <=1)
    {
        printf("Incorrect input. No arguments entered.\n");
        printf("Please enter one or more inputs.\n");
        exit(0);
    }
    
    int i = 0;
    int copy[argc-1];
    for(i; i < (argc -1); i++)
    {
        copy[i] = atoi(argv[i+1]);
    }
        
    pthread_t thread1, thread2, thread3;
    const char *message1 = "This is Thread 1";
    const char *message2 = "This is Thread 2";
    const char *message3 = "This is Thread 3";
    int  t1, t2, t3;
 
    printf("Running: %s\n\n", argv[0]);
    
    datastruct ds = {argc - 1, copy};
 
    /* Create independent threads each of which will execute appropriate function*/
    /* https://man7.org/linux/man-pages/man3/pthread_create.3.html*/
    /* https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-pthread-attr-init-initialize-thread-attribute-object*/
    t1 = pthread_create(&thread1, NULL, (void *) avg_func, (void *) &ds);
    if(t1)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", t1);
        exit(EXIT_FAILURE);
    }
 
    t2 = pthread_create(&thread2, NULL, (void *) min_func, (void *) &ds);
    if(t2)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",t2);
        exit(EXIT_FAILURE);
    }
     
    t3 = pthread_create(&thread3, NULL, (void *) max_func, (void *) &ds);
    if(t3)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", t3);
        exit(EXIT_FAILURE);
    }
 
    printf("pthread_create() for Thread 1 returns: %d\n",t1);
    printf("pthread_create() for Thread 2 returns: %d\n",t2);
    printf("pthread_create() for Thread 3 returns: %d\n\n",t3);
 
    /* Wait till threads are complete before main continues. */
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
 
    printf("The average:  %g\n", avg);
    printf("The minimum:  %d\n", min);
    printf("The maximum:  %d\n", max);
 
    exit(EXIT_SUCCESS);
}
 
void *avg_func(void *ptr)
{
    datastruct * ds;
    ds = (datastruct *) ptr;
    
    int sz = ds->size;
    int i;
    
    for(i = 0; i < sz; i++)
    {
        avg += (ds->values[i]);
    }
    avg = (avg / sz);          
}

void *min_func(void *ptr)
{
    datastruct * ds;
    ds = (datastruct *) ptr;
    
    int sz = ds->size;
    int i;
    
    min = (ds->values[0]);
    for(i = 1; i < sz; i++)
    {
        if(min > (ds->values[i]))
        {
            min = (ds->values[i]);
        }
    }
}

void *max_func(void *ptr)
{
    datastruct * ds;
    ds = (datastruct *) ptr;
    
    int sz = ds->size;
    int i;
    
    max = ds->values[0];
    
    for(i = 1; i < sz; i++)
    {
        if(max < ds->values[i])
        {
            max = ds->values[i];
        }
    }
}
