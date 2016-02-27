CXX=g++
#CXX=clang
CXXFLAGS=-Wall -std=c++11 


SRCS=$(wildcard *.cpp)

OBJS=$(subst .cpp,.o,$(SRCS))

all:

	$(CXX) $(CXXFLAGS) -c $(SRCS)
	$(CXX) $(CXXFLAGS) -o block.x $(OBJS)

	$(echo Done compiling.)

clean:
	rm $(OBJS)
