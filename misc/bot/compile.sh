#!/bin/bash
g++ script.cpp -o bin/script `pkg-config --cflags --libs QtGui QtCore opencv` -lX11 -lXtst 
