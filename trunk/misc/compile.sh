#!/bin/bash
if [ -a $1.cpp ]; then
    g++ $1.cpp -o $1 `pkg-config --cflags --libs opencv` 
    echo "$1.cpp compiled into object $1"
else
    echo './compile.sh prog'
    echo 'This compiles prog.ccp into binary prog'
fi
