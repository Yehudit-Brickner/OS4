#include <stdio.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Creates a test lock */
int main (int argc, char* argv[])
{
	char* file = argv[1];

	if(argc!=2) {

		printf("file does not exist\n");
		exit(1);
	}

	struct flock lock, savelock;
	int fd;

	fd = open(file, O_RDONLY);

	lock.l_type = F_RDLCK;
	lock.l_start = 0;
	lock.l_whence = SEEK_SET;
	lock.l_len = 50;

	savelock = lock;

	fcntl(fd, F_GETLK, &lock);

	while(lock.l_type == F_WRLCK)
	{
		printf("File is locked by process %ld.\n", lock.l_pid);
		exit(1);
	}
	printf("file is not locked\n");


}
