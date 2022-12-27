CC= gcc
CFLAGS=-I.
FLAG=-Wall -g


all: cond packet mutex fcntl

# main: main.o
# 	$(CC) -pthread -o main main.c $(FLAG)

run: cond packet mutex fcntl
	./cond 
	./packet
	./mutex
	./fcntl


cond: cond.o
	$(CC) -pthread -o cond cond.c $(FLAG)


packet: packet.o
	$(CC) -o packet packet.c $(FLAG)


mutex: mutex.o
	$(CC) -pthread -o mutex mutex.c $(FLAG)

fcntl: fcntl.o
	$(CC) -o fcntl fcntl.c $(FLAG)

.PHONY:clean

clean: 
	rm -f *.o cond packet mutex fcntl