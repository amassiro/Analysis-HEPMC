CC = $(CC_ENV)
#CC = g++
#CC = /usr/bin/g++-4.4
CCFLAGS = -Wall -g
SOURCES =
ROOFITLIBS = -lRooFit -lRooFitCore -lMinuit -lFoam
ROOSTATSLIBS = -lRooStats
TMVA = -L${ROOTSYS}lib -lTMVA
DELPHES = -I.

# root
ROOTCFLAGS = $(shell root-config --cflags)
ROOTGLIBS = $(shell root-config --glibs)

# boost
BOOSTFLAGS = $(BOOSTFLAGS_ENV)
BOOSTLIBS = $(BOOSTLIBS_ENV)

# File names
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = $(SOURCES:.cpp=.exe)

# all
all: $(EXEC)


# To compile
%.exe: %.o ExRootTreeReader.o
# 	$(CC) $(CCFLAGS) $(ROOTGLIBS) -L`pwd` -lDelphes ExRootTreeReader.o $< -o $@
	$(CC) $(CCFLAGS) -L`pwd` -lDelphes ExRootTreeReader.o $< $(ROOTGLIBS) $(BOOSTLIBS) -o $@

# To obtain object files
%.o: %.cpp
# 	$(CC) -c $(CCFLAGS) $(ROOTCFLAGS) $(DELPHES) $< -o $@
	$(CC) -c $(CCFLAGS) $(ROOTCFLAGS) $(BOOSTFLAGS) $(DELPHES) $< -o $@

# needed everywhere: ExRootTreeReader
ExRootTreeReader.o: ExRootAnalysis/ExRootTreeReader.cc ExRootAnalysis/ExRootTreeReader.h
	$(CC) $(CCFLAGS) $(DELPHES) -c ExRootAnalysis/ExRootTreeReader.cc $(ROOTCFLAGS) $(ROOTGLIBS)

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

