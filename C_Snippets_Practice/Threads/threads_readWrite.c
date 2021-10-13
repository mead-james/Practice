/*
    Designed for Udemy OS course, problem set 1
    Implements a reader/writer scenario for multithreading
    Multiple reader/writer threads access a shared variable:
        - Any number of readers can access as long as no writer is present
        - Only one writer can access
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define constants
#define NUM_THREADS 5
#define NUM_RUNS 3

pthread_mutex_t m;
// Single condition var used for both r/w; could implement one for each
pthread_cond_t cond_rw;

int gloVal = 0; // Used as the common read/writable var
int indirect = 0; // Used to establish condition var

void* reader() {
    for(int i=0;i<NUM_RUNS;i++) {
        // Enter critical section
        pthread_mutex_lock(&m);
        while(indirect == -1) {
            pthread_cond_wait(&cond_rw,&m);
        }
        indirect += 1;
        pthread_mutex_unlock(&m);

        printf("Reading gloVal... %d\nReaders present: %d\n\n", gloVal, indirect);

        // Exit critical section
        pthread_mutex_lock(&m);
        indirect -= 1;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&cond_rw);
        sleep(rand() % 3);
    }
    pthread_exit(0);
}

void* writer() {
    for(int i=0;i<NUM_RUNS;i++) {
        // Enter critical section
        pthread_mutex_lock(&m);
        while(indirect != 0) {
            pthread_cond_wait(&cond_rw,&m);
        }
        indirect = -1;
        pthread_mutex_unlock(&m);
        
        gloVal += 1;
        printf("gloVal written to... %d\nReaders present: %d\n\n", gloVal, indirect);

        // Exit critical section
        pthread_mutex_lock(&m);
        indirect = 0;
        pthread_mutex_unlock(&m);
        
        pthread_cond_broadcast(&cond_rw);
        sleep(rand() % 3);
    }
    pthread_exit(0);
}

int main() {
    // Init pthread vars and seed rand() for future use
    pthread_mutex_init(&m,NULL);
    pthread_cond_init(&cond_rw,NULL);
    pthread_cond_init(&cond_rw,NULL);
    srand(time(NULL));

    // Declare r/w threads (using common # for r/w arrays, could separate)
    pthread_t r[NUM_THREADS];
    pthread_t w[NUM_THREADS];

    // Generate threads (one loop used for both r/w, could separate)
    for(int i=0;i<NUM_THREADS;i++) {
        if(pthread_create(&r[i],NULL,&reader,NULL) != 0) {return 1;}
        if(pthread_create(&w[i],NULL,&writer,NULL) != 0) {return 1;}
    }

    // Join threads (one loop used for both r/w, could separate)
    for(int i=0;i<NUM_THREADS;i++) {
        if(pthread_join(r[i],NULL) != 0) {return 1;}
        if(pthread_join(w[i],NULL) != 0) {return 1;}
    }

    // Destroy pthread vars after usage
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond_rw);
    pthread_cond_destroy(&cond_rw);

    system("pause");
    return 0;
}