#
#	File : Makefile
#

UTILS= average bound normalize interval round process
CC=gcc
CFLAGS=-Wall 
LDFLAGS=-lm

all: $(UTILS)

clean : 
	rm $(UTILS)

check :
	$(MAKE) -C ../tests check

