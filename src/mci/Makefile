#TODO: document this

CXX	:= g++
AR  := ar
CP  := cp
RM  := rm
CXXFLAGS := -g -O2 -Wall
LIBDIR := ../../lib
INCLUDEDIR := ../../include
INCLUDES := -I $(INCLUDEDIR) `pkg-config --cflags opencv`
LIBS     := -L $(LIBDIR) `pkg-config --libs opencv`

all: libmci.a 

libmci.a: mci.o
	$(AR) rcs $(LIBDIR)/$@ $< 
	$(CP) *.h $(INCLUDEDIR)/.

descend:
	for x in `ls -d */`; do \
		make -C $$x; \
	done;

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
