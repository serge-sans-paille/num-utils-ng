#
#	File : Makefile
#

UTILS= average bound normalize interval round process
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
	for util in $(UTILS) ; do \
		$(RM) $$util $$util.o ; done

check : checkaverage checkround checkinterval

checkaverage :
	../tests/testaverage.sh

checkround :
	../tests/testround.sh

checkinterval :
	../tests/testinterval.sh
