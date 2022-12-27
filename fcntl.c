#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#define BILLION  1000000000L;

//https://chat.openai.com/chat

int main(){
	
    int clock_gettime (clockid_t  clockid,  struct timespec  *tp);
    struct timespec start, stop;
    double accum;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
        perror( "clock gettime" );
        return -1;
    }
    int fd = open("file.txt", O_RDWR);

    // Set up the flock structure
    struct flock mylock;
    mylock.l_type = F_WRLCK;  // Set the type of lock to be a write lock
    mylock.l_whence = SEEK_SET;  // Set the lock to start at the beginning of the file
    mylock.l_start = 0;  // Offset from l_whence is 0
    mylock.l_len = 0;  // Lock the entire file


    for (int i=0; i<1000000; i++){
       // Perform the lock
        mylock.l_type=F_WRLCK;
        fcntl(fd, F_SETLK, &mylock);
        // Unlock the file
        mylock.l_type = F_UNLCK;  // Set the type of lock to be an unlock
        fcntl(fd, F_SETLK, &mylock);
    }
    close(fd);

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ){
        perror( "clock gettime" );
        return -1;
    }
    accum = ( stop.tv_sec - start.tv_sec )+ (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;
    printf( "fcntl took %lf seconds \n", accum );
    return 0;
}
