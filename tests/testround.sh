#!/bin/bash

#This script should gather all the tests for the function round.
ERROR_NB=0
LAST_ERROR=0


../src/round ../tests/test2 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of empty files does not work properly"
  ERROR_NB=1
fi

../src/round ../tests/test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=2
fi

../src/round -blabla ../tests/test3 2>a
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR_NB=3
fi



../src/round >a << STOP 
1.4
STOP
if [ "`cat a`" != "result : 1" ] 
then
  echo -e "The round function does not work properly with stdin"
  ERROR_NB=10
fi

../src/round >a << STOP 
1.6
STOP
if [ "`cat a`" != "result : 2" ] 
then
  echo -e "The round function does not work properly"
  ERROR_NB=10
fi



../src/round  -f >a << STOP 
1.4
STOP
if [ "`cat a`" != "result : 1" ] 
then
  echo -e "The option \"-f\" (floor) does not work properly"
  ERROR_NB=10
fi

../src/round -f >a << STOP 
1.6
STOP
if [ "`cat a`" != "result : 1" ] 
then
  echo -e "The option \"-f\" (floor) does not work properly"
  ERROR_NB=10
fi



../src/round  -c >a << STOP 
1.4
STOP
if [ "`cat a`" != "result : 2" ] 
then
  echo -e "The option \"-c\" (ceiling) does not work properly"
  ERROR_NB=10
fi

../src/round -c >a << STOP 
1.6
STOP
if [ "`cat a`" != "result : 2" ] 
then
  echo -e "The option \"-c\" (ceiling) does not work properly"
  ERROR_NB=10
fi



../src/round  -n 10 >a << STOP 
14
STOP
if [ "`cat a`" != "result : 10" ] 
then
  echo -e "The option \"-n\" does not work properly"
  ERROR_NB=10
fi

../src/round -n 10 >a << STOP 
16
STOP
if [ "`cat a`" != "result : 20" ] 
then
  echo -e "The option \"-n\" does not work properly"
  ERROR_NB=10
fi



if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on round went well"
fi

rm a

exit $ERROR_NB
