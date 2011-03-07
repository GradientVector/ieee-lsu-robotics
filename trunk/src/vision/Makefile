#TODO: document this

CXX	:= g++
AR  := ar
CP  := cp
RM  := rm
CXXFLAGS := -g -O2 -Wall
INCLUDES := -I include/ `pkg-config --cflags opencv`
LIBS     := -L lib/ `pkg-config --libs opencv`
LIBDIR := ../../lib
INCLUDEDIR := ../../include
BINDIR := ../../bin

all: cameratest

cameratest: cameratest.o
	$(CXX) $< -o $(BINDIR)/$@ $(LIBS)


libvision.a:vison.o
	$(AR) rcs $(LIBDIR)/$@ $< 
	$(CP) *.h $(INCLUDEDIR)/.

descend:
	for x in `ls -d */`; do \
		make -C $$x; \
	done;

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
