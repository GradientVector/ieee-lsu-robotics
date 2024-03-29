#!/usr/bin/python
# Beagleboard user button
# Copyright 2009 mechomaniac.com
import struct
inputDevice = "/dev/input/event0"
# format of the event structure (int, int, short, short, int)
inputEventFormat = 'iihhi'
inputEventSize = 16
 
file = open(inputDevice, "rb") # standard binary file input
event = file.read(inputEventSize)
while event:
  (time1, time2, type, code, value) = struct.unpack(inputEventFormat, event)
  if type == 1 and code == 276 and value == 1:
    print "User button pressed!"
    import os
    cmd = './a.out' # modify this according to what we call our final executable
    os.system(cmd)
  event = file.read(inputEventSize)
file.close()
