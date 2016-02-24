CXX=g++
#CXX=clang
CXXFLAGS=-Wall -std=c++11


SRCS=$(wildcard *.cpp)

OBJS=$(subst .cpp,.o,$(SRCS))

System: $(OBJS)

	$(echo Done compiling.)

clean:
	rm $(OBJS)
