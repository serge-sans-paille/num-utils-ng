#!/bin/bash

#This script should gather all the tests for the function numbound.

ERROR_NB=0
LAST_ERROR=0


#../src/numbound ../tests/test3 2>/dev/null
#LAST_ERROR=$?
#if [ "$LAST_ERROR" -ne "1" ] 
#then
#  echo -e "The detection of type error does not work properly"
#  ERROR_NB=3
#fi



../src/numbound -bfr ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR_NB=2
fi


../src/numbound ../tests/dsdsd 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "The detection of a file which can't be open does not work properly"
  ERROR_NB=4
fi


if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on numbound went well"
fi


exit $ERROR_NB
