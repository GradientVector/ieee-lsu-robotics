CXX	:= g++
AR  := ar
CP  := cp
RM  := rm
CXXFLAGS := -g -O2 -Wall
INCLUDES := -I include/ `pkg-config --cflags opencv`
LIBS     := -L lib/ `pkg-config --libs opencv`
LIBDIR := ../../lib
INCLUDEDIR := ../../include

all: 
	for x in `ls -d */`; do \
		make -C $$x; \
	done;

