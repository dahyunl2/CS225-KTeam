EXENAME = main
TEST = test

EXE_OBJ = main.o
OBJS = code/graph.o code/airport.o code/Flight.o main.o 

CXX = clang++
CXXFLAGS = $(CS225) -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

.PHONY: all test clean output_msg

all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

