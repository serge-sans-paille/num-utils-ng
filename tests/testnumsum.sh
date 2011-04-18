#!/bin/sh

# testnumsum.sh
# 
# Copyright 2011 __MyCompanyName__. All rights reserved.


#This script should gather all the tests for the function numsum.

ERROR_NB=0
LAST_ERROR=0

../src/numsum ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=1
fi

../src/numsum -blabla ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of option's error does not work properly"
  ERROR_NB=2
fi


if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on numsum went well"
fi


exit $ERROR_NB


