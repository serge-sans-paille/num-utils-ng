#!/bin/sh
# no option, file check leaks
if which valgrind &>/dev/null
then
	seq 1 10000 > data
	if valgrind numaverage -M data 2>&1 | grep -q '\(leaks\|alloc\)'
	then
		rm -f data
	else
		exit 1
	fi
else
  echo "test skipped, valgrind not found"
  exit 0
fi

