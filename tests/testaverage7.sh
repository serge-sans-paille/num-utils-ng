#!/bin/sh
# no option, pipe, check leaks
if which valgrind &>/dev/null
then
  seq 1 100000 | valgrind numaverage -M 2>&1 | grep -q '\(leaks\|alloc\)'
else
  echo "test skipped, valgrind not found"
  exit 0
fi
