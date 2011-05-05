#!/bin/bash

#This script should gather all the tests for the function numnormalize.

LAST_ERROR=0
ERROR=0

echo -e "===========================================================================\nTest results for the numnormalize function :\n" > finalmsg


echo "1 2 3 4" 1>data
numnormalize -blabla data &>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "/!\ The detection of option failure does not work properly" >>finalmsg
  ERROR=1
fi

echo -e "azeref \n efsef ef\n er" 1>data
numnormalize data &>/dev/null
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
  valgrind numnormalize data &>temp
  grep '\(leaks\|alloc\)' temp >> finalmsg 
  rm temp
fi

echo `seq 1 100` 1> data2
/usr/bin/time -a -o ./finalmsg -f "time taken for 100 numbers : %e seconds\nused memory : %K" numnormalize data2 >/dev/null


echo -e "\t 2.Different normalization option : " >> finalmsg

if [ -e /usr/bin/valgrind ]
then
 valgrind numnormalize -R 0..5 data &>temp
 grep '\(leaks\|alloc\)' temp >> finalmsg 
 rm temp
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 100 numbers : %e seconds\nused memory : %K" numnormalize -R 0..5 data2 >/dev/null 


if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on numnormalize went well\n" >> finalmsg
fi

cat finalmsg

rm finalmsg
rm data
rm data2
exit $ERROR

