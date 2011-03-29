#!/bin/bash

#This script should gather all the tests for the function normalize.
ERROR_NB=0
LAST_ERROR=0



../src/normalize ../tests/test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=2
fi


../src/normalize -bfr ../tests/test3 2>a
LAST_ERROR=$? 
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR_NB=3
fi


../src/normalize ../tests/dsdsd 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "4" ] 
then
  echo -e "The detection of a file which can't be open does not work properly"
  ERROR_NB=4
fi


if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on normalize went well"
fi

rm a

exit $ERROR_NB
