CC = gcc
FLAGS = -c -std=gnu99
COMP = -o
THREAD = -lpthread
MATH = -lm

all:MirrorServer.o ContentServer.o MirrorInitiator.c
	$(CC) $(COMP) server MirrorServer.o $(THREAD) $(MATH)
	$(CC) $(COMP) cserver ContentServer.o $(THREAD)
	$(CC) $(COMP) client MirrorInitiator.c

MirrorServer.o:MirrorServer.c
	$(CC) $(FLAGS) MirrorServer.c
ContentServer.o:ContentServer.c
	$(CC) $(FLAGS) ContentServer.c
clean:
	rm -r MirrorServer.o ContentServer.o server cserver client
