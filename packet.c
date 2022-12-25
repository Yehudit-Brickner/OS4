#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <wait.h>
#include <time.h>

#define BILLION  1000000000L;

int main(void){
    int sv[2]; /* the pair of socket descriptors */
    char buf; /* for data exchange between processes */

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        exit(1);
    }

    int clock_gettime (clockid_t  clockid,  struct timespec  *tp);
    struct timespec start, stop;
    double accum;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
        perror( "clock gettime" );
        return -1;
    }



    for (int i=0; i<1000000;i++){
        // if (i%100000==0){
        //     printf("%d\n",i);
        // }
        if (!fork()) {  /* child */
            read(sv[1], &buf, 1);
            // printf("child: read '%c'\n", buf);
            buf = toupper(buf);  /* make it uppercase */
            write(sv[1], &buf, 1);
            // printf("child: sent '%c'\n", buf);
            exit(0);

        } else { /* parent */
            write(sv[0], "b", 1);
            // printf("parent: sent 'b'\n");
            read(sv[0], &buf, 1);
            // printf("parent: read '%c'\n", buf);
            wait(NULL); /* wait for child to die */
            
        }
    }
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ){
        perror( "clock gettime" );
        return -1;
    }
    accum = ( stop.tv_sec - start.tv_sec )+ (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;
    printf("quick full-duplex pipes took %lf seconds \n", accum );
    return 0;
}