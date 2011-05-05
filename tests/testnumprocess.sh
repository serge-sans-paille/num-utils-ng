#!/bin/bash

#This script should gather all the tests for the function numprocess.

ERROR=0
LAST_ERROR=0

echo -e "===========================================================================\nTest results for the numprocess function :\n" > finalmsg

echo -e "azeref \n efsef ef\n er" 1>data
numprocess /+1/ data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "/!\ The detection of type error does not work properly"
  ERROR=1
fi

echo "1 2 3 4" >data
numprocess -blabla data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "/!\ The detection of option failure does not work properly"
  ERROR=2
fi

numprocess 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "/!\ The detection of missing expression does not work properly"
  ERROR=3
fi

numprocess rge data 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "4" ] 
then
  echo -e "/!\ The detection of wrong expressions does not work properly"
  ERROR=4
fi

echo -e "\t 1.Addition :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  echo `seq 1 100` 1> data
  valgrind numprocess /+1/ data &>tempo
  grep '\(leaks\|alloc\)' tempo >> finalmsg 
  rm tempo
fi

echo `seq 1 10000` 1> data2
/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /+1/ data2 >/dev/null 

echo -e "\t 2.Substraction :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /-1/ data &>tempo
  grep '\(leaks\|alloc\)' tempo >> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /-1/ data2 >/dev/null 

echo -e "\t 3.Multiplication :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /*2/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /*2/ data2 >/dev/null 

echo -e "\t 4.Division :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /%2/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /%2/ data2 >/dev/null 

echo -e "\t 5.Power :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /^2/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /^2/ data2 >/dev/null 

echo -e "\t 6.Square root :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /sqrt/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /sqrt/ data2 >/dev/null 

echo -e "\t 7.Cosinus :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /cos/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /cos/ data2 >/dev/null 

echo -e "\t 8.Sinus :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /sin/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /sin/ data2 >/dev/null 

echo -e "\t 9.Use of constants :" >> finalmsg

if [ -e /usr/bin/valgrind ]
then
  valgrind numprocess /*pi/ data &>tempo
  grep '\(leaks\|alloc\)' tempo>> finalmsg 
  rm tempo
fi

/usr/bin/time -a -o ./finalmsg -f "time taken for 10000 numbers : %e seconds\nused memory : %K" numprocess /*pi/ data2 >/dev/null 

if [ "$ERROR" -eq "0" ] 
then
  echo -e "\nAll tests on numprocess went well\n" >> finalmsg
fi

cat finalmsg
rm finalmsg
rm data
rm data2
exit $ERROR
