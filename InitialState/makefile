CXX=g++
CXXFLAGS=-Wall -std=c++11


SRCS=$(wildcard *.cpp)

OBJS=$(subst .cpp,.o,$(SRCS))

InitialState: $(OBJS)

	$(echo Done compiling.)

clean:
	rm $(OBJS)
