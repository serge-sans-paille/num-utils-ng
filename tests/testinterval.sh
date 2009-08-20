#!/bin/bash

#This script should gather all the tests for the function interval.

ERROR=0
LAST_ERROR=0

echo -e "\nTest results for the interval function :\n" > finalmsg

echo "1 2 3 4" 1> data

interval .data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "/!\ The detection of type error does not work properly"
  ERROR=1
fi

echo -e "azeref \n efsef ef\n er" 1>data
interval -blabla data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "/!\ The detection of option's error does not work properly"
  ERROR=2
fi


if [ -e /usr/bin/valgrind ]
then
  echo `seq 1 100` 1> data
  valgrind interval data &>temp
  grep '\(leaks\|alloc\)' temp >> finalmsg 
  rm temp
fi

echo `seq 1 100000` 1> data2
/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" interval data2 >/dev/null 

cat finalmsg
if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on interval went well\n"
fi


exit
