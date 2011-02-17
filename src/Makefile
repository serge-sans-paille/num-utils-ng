
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

check : check4 check1 check2 check3 check5 

check1 : 
	./$(EXEC) ../tests/test1  #this test should work

check2 :
	./$(EXEC) ../tests/test2  #test2 is empty

check3 :
	./$(EXEC) ../tests/test3  #test3 contains letters

check4 :
	./$(EXEC) -i ../tests/test1  #this test should work

check5 :
	./$(EXEC) -I ../tests/test1  #this test should work
