OBJS	= mymalloc.o memgrind.o correctnessTest.o
SOURCE	= mymalloc.c memgrind.c correctnessTest.c
HEADER	= mymalloc.h
OUT	= z.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

mymalloc.o: mymalloc.c
	$(CC) $(FLAGS) mymalloc.c 

memgrind.o: memgrind.c
	$(CC) $(FLAGS) memgrind.c 

correctnessTest.o: correctnessTest.c
	$(CC) $(FLAGS) correctnessTest.c 


clean:
	rm -f $(OBJS) $(OUT)