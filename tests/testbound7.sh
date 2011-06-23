#!/bin/sh
if which valgrind &>/dev/null
then
	seq 1 100000 | valgrind numbound 2>&1 | grep -q '\(leaks\|alloc\)'
else
	echo "test skipped, valgrind not found"
	exit 0
fi
