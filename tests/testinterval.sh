#!/bin/bash

#This script should gather all the tests for the function numinterval.

ERROR=0
LAST_ERROR=0

echo -e "===========================================================================\nTest results for the numinterval function :\n" > finalmsg

echo -e "azeref \n efsef ef\n er" 1>data
numinterval .data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "/!\ The detection of type error does not work properly" >>finalmsg
  ERROR=1
fi

echo "1 2 3 4" 1> data
numinterval -blabla data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "/!\ The detection of option's error does not work properly" >>finalmsg
  ERROR=2
fi


if [ -e /usr/bin/valgrind ]
then
  echo `seq 1 100` 1> data
  valgrind numinterval data &>temp
  grep '\(leaks\|alloc\)' temp >> finalmsg 
  rm temp
fi

echo `seq 1 10000` 1> data
/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numinterval data >/dev/null 

if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on numinterval went well\n" >> finalmsg
fi

cat finalmsg

rm data
rm finalmsg
exit $ERROR
