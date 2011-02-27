#!/bin/bash

#This script should gather all the tests for the function average.
ERROR_NB=0
LAST_ERROR=0


../src/average ./test2 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of empty files does not work properly"
  ERROR_NB=1
fi


../src/average ./test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=2
fi

../src/average -blabla ./test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR_NB=2
fi

../src/average >a << STOP 
1
2
3
4
5
STOP
if [ "`cat a`" != "result : 3.000000" ] 
then
  echo -e "The average function does not work properly with stdin"
  ERROR_NB=10
fi


../src/average ./test1 >a
if [ "`cat a`" != "result : 4.220000" ] 
then
  echo -e "The average function does not work properly with a file"
  ERROR_NB=11
fi


../src/average -M ./test1 >a
if [ "`cat a`" != "result : 4.220000" ] 
then
  echo -e "The "-M" (median) option does not work properly"
  ERROR_NB=12
fi


../src/average -Ml ./test1 >a
if [ "`cat a`" != "result : 4.220000" ] 
then
  echo -e "The "-Ml" (median) option does not work properly"
  ERROR_NB=13
fi


../src/average -m ./test1 >a
if [ "`cat a`" != "result : 4.220000" ] 
then
  echo -e "The "-m" (mode) option does not work properly"
  ERROR_NB=14
fi


../src/average -i ./test1 >a
if [ "`cat a`" != "result : 4" ] 
then
  echo -e "The "-i" (integer portion) option does not work properly"
  ERROR_NB=15
fi


../src/average -I ./test1 >a
if [ "`cat a`" != "result : 0.220000" ] 
then
  echo -e "The "-I" (decimal portion) option does not work properly"
  ERROR_NB=16
fi


../src/average -Mi ./test1 >a
if [ "`cat a`" != "result : 4" ] 
then
  echo -e "The "-Mi" (integer portion of median) option does not work properly"
  ERROR_NB=17
fi


../src/average -MI ./test1 >a
if [ "`cat a`" != "result : 0.220000" ] 
then
  echo -e "The "-MI" (decimal portion of median) option does not work properly"
  ERROR_NB=18
fi


../src/average -mi ./test1 >a
if [ "`cat a`" != "result : 4" ] 
then
  echo -e "The "-mi" (integer portion of mode) option does not work properly"
  ERROR_NB=19
fi


../src/average -mI ./test1 >a
if [ "`cat a`" != "result : 0.220000" ] 
then
  echo -e "The "-mI" (decimal portion of mode) option does not work properly"
  ERROR_NB=20
fi

if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests went well"
fi

rm a

exit $ERROR_NB
