#!/bin/bash

#This script should gather all the tests for the function interval.

ERROR_NB=0
LAST_ERROR=0

../src/interval ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=1
fi

../src/interval -blabla ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of option's error does not work properly"
  ERROR_NB=2
fi


if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on interval went well"
fi


exit $ERROR_NB
