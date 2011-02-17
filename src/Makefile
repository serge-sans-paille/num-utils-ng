
#	File : Makefile
#	Compile the file "average"

EXEC=average
CC=gcc
CFLAGS=-Wall 
LIBS=-lm

all: $(EXEC) 

average: $(EXEC).o 
	$(CC) $(CFLAGS) -o $(EXEC) $(EXEC).o
average.o : average.c
	$(CC) $(CFLAGS) -c $(EXEC).c

clean : 
	$(RM) $(EXEC) $(EXEC).o

check : check1 check2 check3

check1 : 
	./$(EXEC) ../tests/test1

check2 :
	./$(EXEC) ../tests/test2

check3 :
	./$(EXEC) ../tests/test3
