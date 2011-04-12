CXX	:= g++
AR  := ar
CP  := cp
RM  := rm
CXXFLAGS := -g -O2 -Wall
INCLUDES := -I include/ `pkg-config --cflags opencv`
LIBS     := -L lib/ `pkg-config --libs opencv`
LIBDIR := lib
INCLUDEDIR := include
BINDIR := bin

DIRS  := src

all: descend 

cameratest: cameratest.o
	$(CXX) $< -o $(BINDIR)/$@ $(LIBS)
	$(RM) $<

descend:
	for x in $(DIRS); do \
		make -C $$x; \
	done;

clean:
	rm lib/*; 
	rm include/*

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
