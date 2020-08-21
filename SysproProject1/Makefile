OBJS=main.o MaxHeap.o Operations.o
SOURCE=main.c MaxHeap.c Operations.o
HEADER= Operations.h MaxHeap.h
OUT=myexe
CC=gcc
FLAGS=-g -c 

all:$(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm

main.o: main.c
	$(CC) $(FLAGS) main.c

MaxHeap.o : MaxHeap.c 
	$(CC) $(FLAGS) MaxHeap.c

Operations.o : Operations.c 
	$(CC) $(FLAGS) Operations.c

clean: 
	rm -f Operations.o MaxHeap.o main.o  $(OUT)

count:
	wc $(SOURCE) $(HEADER)
