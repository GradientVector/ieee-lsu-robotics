#TODO: document this
#CXX = refence to the compiler, g++ in this case
#CXXFLAGS = compiler options
#-Wall = warn user of all potential errors
#LIBDIR = Relative path to the directory to which archive files defined by the LIBRARY macro will be written
#"-I.." = tells the compiler where to look for header files if they are not found in your working directory or 
#         the standard places where [e.g.] iostream is found
# "-L.." = directive to specify which directory to look for libraries if they arent in the standard places
#AR = Archive-maintaining program; default ‘ar’. 
#CP = copy
#RM = remove
#
#%.o: %.cpp
#	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
# ^^^ defines a rule that can make any file x.o from x.cpp

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
