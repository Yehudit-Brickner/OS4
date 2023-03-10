#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Creates a write lock on a file */
int main (int argc, char* argv[])
{
	char* file = argv[1];
	int fd;
	struct flock lock;

	printf ("my pid is %d\n", (int) getpid ());

	printf ("opening %s\n", file);

	/* Open a file descriptor to the file */
	fd = open (file, O_WRONLY);
	printf ("locking\n");

	/* Initialize the flock structure */
	memset (&lock, 0, sizeof(lock));
    printf ("locked; hit enter to unlock... ");
    for (size_t i = 0; i < 1000000; i++)
    {
        lock.l_type = F_WRLCK;

	/* Place a write lock on the file */
	fcntl (fd, F_SETLKW, &lock);
    }
    

	printf ("locked; hit enter to unlock... ");

	/* Wait for the user to hit enter */
	getchar ();

	printf ("unlocking\n");

	/* Release the lock */
	lock.l_type = F_UNLCK;
	fcntl (fd, F_SETLKW, &lock);

	close (fd);
	return 0;
}
