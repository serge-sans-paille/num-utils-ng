#!/bin/sh
# no option, reading from a file
seq 1 100 > data
if test "`numaverage data`" = "50.500000" ;
then
	rm -f data
	exit 0
else
	exit 1
fi
