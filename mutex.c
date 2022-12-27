
#include <stdbool.h>
#include <stdio.h>
// #include <zconf.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define BILLION  1000000000L;

//https://github.com/eirikwha/posix_mutex/blob/master/main.c

bool running = 1;
int var1 = 0;
int var2 = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *myThreadFun1(void *vargp){
    for (size_t i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        var1 = var1 + 1;
        var2 = var1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// void *myThreadFun2(void *vargp){
//     int i;
      
//     // printf("Number 1 is %i, number 2 is %i\n", var1,var2);
//     // usleep(100000);
//     // running = 0;
//     // exit(0);
// }

int main(){
    pthread_t thread_id1;

    // printf("Comparing variables var 1 and 2:\n");

    int clock_gettime (clockid_t  clockid,  struct timespec  *tp);
    struct timespec start, stop;
    double accum;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
        perror( "clock gettime" );
        return -1;
    }

    pthread_create(&thread_id1, NULL, myThreadFun1, NULL);
    // pthread_create(&thread_id1, NULL, myThreadFun2, NULL);
    pthread_join(thread_id1, NULL);


    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ){
        perror( "clock gettime" );
        return -1;
    }
    accum = ( stop.tv_sec - start.tv_sec )+ (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;
    printf("mutex took %lf seconds \n", accum );
    // printf("\nExiting program..\n");
    return 0;
    
}
