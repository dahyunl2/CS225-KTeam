EXENAME = project
TEST = test

EXE_OBJ = main.o
OBJS = graph.o main.o 

CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

test: output_msg tests/tests.cpp graph.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test