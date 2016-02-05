CXX=g++
CXXFLAGS=-Wall -std=c++11 -c

SRCS=$(wildcard *.cpp)

OBJS=$(subst .cpp,.o,$(SRCS))

all:
	for source in $(SRCS); do \
	  $(CXX) $(CXXFLAGS) $$source; \
	done

clean:
	rm $(OBJS)

