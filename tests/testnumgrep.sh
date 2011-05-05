#!/bin/bash

#This script should gather all the tests for the function numgrep.

ERROR=0
LAST_ERROR=0

echo -e "===========================================================================\nTest results for the numgrep function :\n" > finalmsg


echo -e "\t 1.Without options :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  echo `seq 1 100` 1> data
  valgrind numgrep /1..100/ data &>temp
  grep '\(leaks\|alloc\)' temp >> finalmsg 
  rm temp
fi

echo `seq 1 100000` 1> data2
/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" numgrep /1.100/ data2 >/dev/null



if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on numgrep went well\n" >> finalmsg
fi

cat finalmsg

rm finalmsg
rm data
rm data2
exit $ERROR

