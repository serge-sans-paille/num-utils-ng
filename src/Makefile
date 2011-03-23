#
#	File : Makefile
#

UTILS= average bound normalize interval round process
CC=gcc
CFLAGS=-Wall 
LIBS=-lm

all: $(UTILS).o
	for util in $(UTILS) ; do \
		$(CC) $(CFLAGS) $(LIBS) -o $$util $$util.o ; done

$(UTILS).o:
	for util in $(UTILS) ; do \
		$(CC) $(CFLAGS) -c $$util.c ; done

clean : 
	for util in $(UTILS) ; do \
		$(RM) $$util $$util.o ; done

check : checkaverage checkbound checkinterval checkround

checkaverage :
	../tests/testaverage.sh

checkbound :
	../tests/testbound.sh

checkinterval :
	../tests/testinterval.sh

checkround :
	../tests/testround.sh
