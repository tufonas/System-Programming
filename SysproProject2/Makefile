OBJS=jms_coord.o jms_console.o pool.o job.o
SOURCE=jms_coord.c jms_console.c pool.c job.c
OUT=jms_console
OUT1=jms_coord
OUT2=pool
OUT3=job
CC=gcc
FLAGS=-g -c 

all:$(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm

pool.o: pool.c
	$(CC) -o $(OUT2) pool.c

job.o : job.c 
	$(CC) -o $(OUT3) job.c

jms_console.o : jms_console.c 
	$(CC) -o $(OUT) jms_console.c

jms_coord.o : jms_coord.c 
	$(CC) -o $(OUT1) jms_coord.c

clean: 
	rm -f Operations.o MaxHeap.o main.o pool.o $(OUT)

