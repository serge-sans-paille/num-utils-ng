#
#	File : Makefile
#

UTILS= average bound interval round process
CC=gcc
CFLAGS=-Wall 
LDFLAGS=-lm

all: check

check : checkaverage checkbound checkinterval checkround checkprocess

checkaverage : ../src/average
	../tests/testaverage.sh

checkbound : ../src/bound
	../tests/testbound.sh

checkinterval : ../src/interval
	../tests/testinterval.sh

checkround : ../src/round
	../tests/testround.sh

checkprocess : ../src/process
	../tests/testprocess.sh

../src/$(UTILS):

