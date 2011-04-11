#!/bin/sh
#
# Read a GPIO input
#
# This script will be called when we boot the beagleboard.
# It will listen for a button push, and call a.out when that happens.
# This code currently assumes main.cpp will be compiled to a.out
#
# Most of this was copied from:
# http://wh1t3s.com/2009/05/14/reading-beagleboard-gpio/
# A lot of code is commented out.

# note: $1 represents the first argument to the script call
GPIO=$1

cleanup() { # Release the GPIO port
  echo $GPIO > /sys/class/gpio/unexport
  echo ""
  echo ""
  exit
}

# Open the GPIO port
#
echo "$GPIO" > /sys/class/gpio/export
echo "in" > /sys/class/gpio/gpio${GPIO}/direction

# TODO
trap cleanup SIGINT # call cleanup on Ctrl-C

THIS_VALUE=`cat /sys/class/gpio/gpio${GPIO}/value`
LAST_VALUE=$THIS_VALUE
NEWLINE=0

# Read forever
while [ "1" = "1" ]; do
  # if the button has just been pressed,
  if [ "$THIS_VALUE" != "$LAST_VALUE" ]; then  
    if [ "1" = "$THIS_VALUE" ]; then
      echo Hello
    fi
  fi

  #  next three lines detect state transition
  # if [ "$THIS_VALUE" != "$LAST_VALUE" ]; then
  #   EV="|"
  # else
  #   EV=""
  # fi
 
  #  "^" for high, '_' for low
  # if [ "1" = "$THIS_VALUE" ]; then
  #   EV="${EV}^"
  # else
  #   EV="${EV}_"
  # fi
  # echo -n $EV

  # sleep for a while
  sleep 0.05

  LAST_VALUE=$THIS_VALUE
  THIS_VALUE=`cat /sys/class/gpio/gpio${GPIO}/value`
  # NEWLINE=`expr $NEWLINE + 1`
  # if [ "$NEWLINE" = "72" ]; then
  #   echo ""
  #   NEWLINE=0
  # fi

done

cleanup # call the cleanup routine
