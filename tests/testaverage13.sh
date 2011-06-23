#!/bin/sh
# using average option, negative values from a pipe, with decimal part
for i in `seq 1 1000`; do echo $i ; done > data
for i in `seq 1 1000`; do echo 1.111 >> data ; done

if test "1.111000" = "`numaverage -m data`" ; then
	rm -f data
else
	exit 1
fi
