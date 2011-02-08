CXX	:= g++
AR  := ar
CP  := cp
RM  := rm
CXXFLAGS := -g -O2 -Wall
INCLUDES := -I include/ `pkg-config --cflags opencv`
LIBS     := -L lib/ `pkg-config --libs opencv`
LIBDIR := ../../lib
INCLUDEDIR := ../../include

all: libserial.a 

libserial.a: serial.o
	$(AR) rcs $(LIBDIR)/$@ $< 
	$(CP) *.h $(INCLUDEDIR)/.
	$(RM) $<

descend:
	for x in `ls -d */`; do \
		make -C $$x; \
	done;

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
