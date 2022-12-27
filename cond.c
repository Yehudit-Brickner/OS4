
//https://www.geeksforgeeks.org/condition-wait-signal-multi-threading/
//https://www.educba.com/clock_gettime/
// C program to implement cond(), signal()
// and wait() functions
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#define BILLION  1000000000L;



// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;

// Thread function
void* foo(){
	// acquire a lock
	pthread_mutex_lock(&lock);
	if (done == 1) {
		// let's wait on condition variable cond1
		done = 2;
		// printf("Waiting on condition variable cond1\n");
		pthread_cond_wait(&cond1, &lock);
	}
	else {
		// Let's signal condition variable cond1
		// printf("Signaling condition variable cond1\n");
		pthread_cond_signal(&cond1);
	}
	// release lock
	pthread_mutex_unlock(&lock);
	// printf("Returning thread\n");
	return NULL;
}




// Driver code
int main(){
	pthread_t tid1, tid2;
    int clock_gettime (clockid_t  clockid,  struct timespec  *tp);
    struct timespec start, stop;
    double accum;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
        perror( "clock gettime" );
        return -1;
    }
    for (int i=0; i<1000000; i++){
        pthread_create(&tid1, NULL, foo, NULL);
        pthread_create(&tid2, NULL, foo, NULL);
        pthread_join(tid2, NULL);
    }

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ){
        perror( "clock gettime" );
        return -1;
    }
    accum = ( stop.tv_sec - start.tv_sec )+ (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;
    printf( "cond took %lf seconds \n", accum );
    return 0;
}
