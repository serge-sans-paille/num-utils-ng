#!/bin/sh
# using median option, from a file
seq 1 100 > data
if test "`numaverage -M data`" = 51.000000
then
	rm -f data
else
	exit 1
fi
