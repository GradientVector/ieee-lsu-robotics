#TODO: document this

CXX	:= g++
AR  := ar
CP  := cp
RM  := rm
CXXFLAGS := -g -O2 -Wall
LIBDIR := ../../lib
INCLUDEDIR := ../../include
BINDIR := ../../bin
INCLUDES := -I $(INCLUDEDIR) `pkg-config --cflags opencv`
LIBS     := -L $(LIBDIR) `pkg-config --libs opencv` -lserial

all: libserial.a serialtest 

libserial.a: serial.o
	$(AR) rcs $(LIBDIR)/$@ $< 
	$(CP) *.h $(INCLUDEDIR)/.

serialtest: serialtest.o libserial.a
	$(CXX) $< -o $(BINDIR)/$@ $(LIBS)


descend:
	for x in `ls -d */`; do \
		make -C $$x; \
	done;

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
