
#	File : Makefile
#	Compile the file "calculAverage.c"


CC=gcc
CFLAGS=-Wall 
LIBS=-lm

all: calculAverage

calculAverage: calculAverage.o
	$(CC) $(CFLAGS) -o numaverage calculAverage.o

calculAverage.o : calculAverage.c
	$(CC) $(CFLAGS) -c calculAverage.c

clear : clean
	$(RM) -f numaverage

clean :
	$(RM) -f *.o

check : check1 check2 check3 check4

check1: numaverage
	./numaverage ../tests/test1
#read the file and average output

check2: numaverage
	./numaverage ../tests/test2
#this test must fail

check3: numaverage
	./numaverage ../tests/test3
#this test must fail

check4: numaverage
	./numaverage
#input stdin and average output
