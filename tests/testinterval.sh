#!/bin/bash

#This script should gather all the tests for the function interval.
ERROR_NB=0
LAST_ERROR=0


../src/interval ../tests/test2 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of empty files does not work properly"
  ERROR_NB=1
fi

../src/interval ../tests/test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=2
fi

../src/interval >a << STOP 
1
2
STOP
if [ "`cat a`" != "1.000000" ] 
then
  echo -e "The function interval does not work properly with stdin"
  ERROR_NB=10
fi

if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on interval went well"
fi

rm a

exit $ERROR_NB
