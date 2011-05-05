#!/bin/bash

#This script should gather all the tests for the function numaverage.

LAST_ERROR=0
ERROR=0

echo -e "===========================================================================\nTest results for the numaverage function :\n" > finalmsg

echo "1 2 3 4" 1> data
numaverage -blabla data &>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "/!\ The detection of option failure does not work properly" >>finalmsg
  ERROR=1
fi

echo -e "azeref \n efsef ef\n er" 1>data
numaverage data &>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "/!\ The detection of type error does not work properly" >>finalmsg
  ERROR=1
fi

echo -e "\t 1.Without options :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  echo `seq 1 100` 1> data
  valgrind numaverage data &>temp
  grep '\(leaks\|alloc\)' temp >> finalmsg 
  rm temp
fi

echo `seq 1 100000` 1> data2
/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" numaverage data2 >/dev/null 

echo -e "\t 2.Median option : " >> finalmsg

if [ -e /usr/bin/valgrind ]
then
 valgrind numaverage -M data &>temp
 grep '\(leaks\|alloc\)' temp >> finalmsg 
 rm temp
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" numaverage -M data2 >/dev/null 

echo -e "\t 3.Mode option : " >> finalmsg

if [ -e /usr/bin/valgrind ]
then
 valgrind numaverage -m data &>temp
 grep '\(leaks\|alloc\)' temp >> finalmsg 
 rm temp
fi

echo `seq 1 10000` 1> data2
/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numaverage -m data2 >/dev/null 

if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on average went well\n" >> finalmsg
fi

cat finalmsg

rm finalmsg
rm data
rm data2
exit $ERROR
