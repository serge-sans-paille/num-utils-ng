#!/bin/bash

#This script should gather all the tests for the function numrandom.

ERROR=0
LAST_ERROR=0

echo -e "===========================================================================\nTest results for the numrandom function :\n" > finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numrandom /1:1000/ &>tempo
  grep '\(leaks\|alloc\)' tempo >> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" numrandom /1:100000/ >/dev/null 

if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on numrandom went well\n" >> finalmsg
fi

cat finalmsg
rm finalmsg
exit $ERROR
