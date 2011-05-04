#!/bin/bash

#This script should gather all the tests for the function round.

ERROR=0
LAST_ERROR=0

echo -e "===========================================================================\nTest results for the numround function :\n" > finalmsg

echo -e "azeref \n efsef ef\n er" 1>data
numround data &>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "/!\ The detection of type error does not work properly" >>finalmsg
  ERROR=1
fi

numround -blabla data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR=2
fi

if [ -e /usr/bin/valgrind ]
then
  echo `seq 1 100` 1> data
  valgrind numround data &>temp
  grep '\(leaks\|alloc\)' temp >> finalmsg 
  rm temp
fi

echo `seq 1 100000` 1> data
/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" numround data >/dev/null 

if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on numround went well\n" >> finalmsg
fi

cat finalmsg

rm finalmsg
rm data
exit $ERROR
