
#	File : Makefile
#	Compile the file "average"

EXEC=average
EXEC2=bound
CC=gcc
CFLAGS=-Wall 
LIBS=-lm

all: $(EXEC) $(EXEC2) 

average: $(EXEC).o 
	$(CC) $(CFLAGS) -o $(EXEC) $(EXEC).o
average.o : average.c
	$(CC) $(CFLAGS) -c $(EXEC).c

bound: $(EXEC2).o
	$(CC) $(CFLAGS) -o $(EXEC2) $(EXEC2).o

clean : 
	$(RM) $(EXEC) $(EXEC).o
	$(RM) $(EXEC2) $(EXEC2).o

check : check4 check1 check2 check3 check5 check6 check7 check8

check1 : 
	./$(EXEC) ../tests/test1  #this test should work
	./$(EXEC2) ../tests/test1  #this test should work


check2 :
	./$(EXEC) ../tests/test2  #test2 is empty
	./$(EXEC2) ../tests/test2  #test2 is empty

check3 :
	./$(EXEC) ../tests/test3  #test3 contains letters
	./$(EXEC2) ../tests/test3  #test3 contains letters

check4 :
	./$(EXEC) -i ../tests/test1  #this test should work

check5 :
	./$(EXEC) -I ../tests/test1  #this test should work

check6 :
	./$(EXEC2) -l ../tests/test1  #this test should work

check7 :
	./$(EXEC) -M ../tests/test1

check8 :
	./$(EXEC) -m ../tests/test1
