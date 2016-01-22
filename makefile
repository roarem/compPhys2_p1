
CXX=g++
CXXFLAGS=-Wall -std=c++11

SRCS=main.cpp populasjon.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))

main: $(OBJS) 
	$(CXX) -o main.x $(OBJS)

main.o: main.cpp

populasjon.o: populasjon.cpp populasjon.h


clean:
	rm $(OBJS)

