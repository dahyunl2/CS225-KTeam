EXENAME = main
TEST = test

EXE_OBJ = main.o
OBJS = graph.o airport.o Flight.o main.o 

CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean output_msg

# all : $(EXENAME)

# $(EXENAME): $(OBJS)
#       $(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main: main.o code/graph.o code/Flight.o code/airport.o
	$(CC) $(CFLAGS) -o main main.o code/graph.o code/Flight.o code/airport.o

test: code/airport.cpp code/Flight.cpp code/graph.cpp
	$(LD) code/graph.cpp code/airport.cpp code/Flight.cpp $(LDFLAGS) -o test

# main.o: main.cpp graph.o Flight.o airport.o
#    $(CC) $(CFLAGS) -c main.cpp
# graph.o: graph.cpp
#    $(CXX) $< $(CXXFLAGS)
# Flight.o: Flight.cpp
#    $(CXX) $< $(CXXFLAGS)
# airport.o: airport.cpp
#    $(CXX) $< $(CXXFLAGS)

# test: output_msg tests/tests.cpp graph.cpp Flight.cpp airport.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test