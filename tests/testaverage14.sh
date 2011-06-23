#!/bin/sh
# using average option, negative values from a pipe, with decimal part
if which valgrind &>/dev/null
then
	for i in `seq 1 1000`; do echo $i ; done > data
	for i in `seq 1 1000`; do echo 1.111 >> data ; done
	if valgrind numaverage -m data 2>&1 | grep -q '\(leaks\|alloc\)'
	then
		rm -f data
	else
		exit 1
	fi
else
	echo "test skipped, valgrind not found"
	exit 0
fi
