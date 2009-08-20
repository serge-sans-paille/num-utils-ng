#!/bin/bash

#This script should gather all the tests for the function average.

LAST_ERROR=0
ERROR=0

echo -e "\nTest results for the average function :\n" > finalmsg

echo "1 2 3 4" 1> data

average -blabla data &>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "/!\ The detection of option failure does not work properly" >>finalmsg
  ERROR=1
fi

echo -e "azeref \n efsef ef\n er" 1>data
average data &>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "/!\ The detection of type error does not work properly" >>finalmsg
  ERROR=1
fi

echo -e "\t 1.Without options :" >> finalmsg

echo `seq 1 100` 1> data
valgrind average data &>temp
grep '\(leaks\|alloc\)' temp >> finalmsg 
rm temp

echo `seq 1 100000` 1> data
/usr/bin/time -a -o ./finalmsg -f "time taken for 100000 numbers : %e seconds\nused memory : %K" average data >/dev/null 

echo -e "\t 2.Median option : " >> finalmsg

echo `seq 1 100` 1> data
valgrind average -M data &>temp
grep '\(leaks\|alloc\)' temp >> finalmsg 
rm temp

echo `seq 1 10000` 1> data
/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" average -M data >/dev/null 

echo -e "\t 3.Mode option : " >> finalmsg

echo `seq 1 100` 1> data
valgrind average -m data &>temp
grep '\(leaks\|alloc\)' temp >> finalmsg 
rm temp

echo `seq 1 10000` 1> data
/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" average -m data >/dev/null 

cat finalmsg
if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on average went well\n"
fi

rm finalmsg
rm data
exit
