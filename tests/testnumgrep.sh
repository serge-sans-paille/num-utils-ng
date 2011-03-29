#!/bin/bash

#This script should gather all the tests for the function numgrep.
ERROR_NB=0
LAST_ERROR=0


../src/numgrep >a << STOP 
8
STOP
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of a wrong expression does not work properly"
  ERROR_NB=2
fi


../src/numgrep /1..10/ ../tests/dsdsd >a
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
