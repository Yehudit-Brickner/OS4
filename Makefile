CC= gcc
CFLAGS=-I.
FLAG=-Wall -g


all: cond packet

# main: main.o
# 	$(CC) -pthread -o main main.c $(FLAG)

run: cond packet
	./cond 
	./packet


cond: cond.o
	$(CC) -pthread -o cond cond.c $(FLAG)


packet: packet.o
	$(CC) -o packet packet.c $(FLAG)

.PHONY:clean


clean: 
	rm -f *.o cond packet