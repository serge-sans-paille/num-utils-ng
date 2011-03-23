#!/bin/bash

#This script should gather all the tests for the function bound.
ERROR_NB=0
LAST_ERROR=0


../src/bound ../tests/test2 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of empty files does not work properly"
  ERROR_NB=1
fi


../src/bound ../tests/test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=2
fi


../src/bound -bfr ../tests/test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR_NB=3
fi


../src/bound >a << STOP 
4.8
1.4
8.9
STOP
if [ "`cat a`" != "result : 8.900000" ] 
then
  echo -e "The bound function does not work properly"
  ERROR_NB=10
fi


../src/bound -l >a << STOP 
4.8
1.4
8.9
STOP
if [ "`cat a`" != "result : 1.400000" ] 
then
  echo -e "The option \"-l\" (lower number) does not work properly"
  ERROR_NB=20
fi



if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on bound went well"
fi

rm a

exit $ERROR_NB
