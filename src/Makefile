#
#	File : Makefile
#

UTILS= average bound normalize
CC=gcc
CFLAGS=-Wall 
LIBS=-lm

all: $(UTILS).o
	for util in $(UTILS) ; do \
		$(CC) $(CFLAGS) -o $$util $$util.o ; done

$(UTILS).o:
	for util in $(UTILS) ; do \
		$(CC) $(CFLAGS) -c $$util.c ; done

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
