#!/bin/bash

#This script should gather all the tests for the function random.
ERROR_NB=0
LAST_ERROR=0


../src/average /1hjh/ 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of bad argument does not work properly"
  ERROR_NB=1
fi


if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on random went well"
fi

exit $ERROR_NB
