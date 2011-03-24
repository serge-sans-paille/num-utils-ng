#
#	File : Makefile
#

UTILS= average bound interval normalize round
CC=gcc
CFLAGS=-Wall 
LDFLAGS=-lm

all: check

check : checkaverage checkbound checkinterval checknormalize checkround

checkaverage : ../src/average
	../tests/testaverage.sh

checkbound : ../src/bound
	../tests/testbound.sh

checkinterval : ../src/interval
	../tests/testinterval.sh

checknormalize : ../src/normalize
	../tests/testnormalize.sh

checkround : ../src/round
	../tests/testround.sh


../src/$(UTILS):

