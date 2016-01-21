CXX=g++
CXXFLAGS=-Wall -std=c++11

SRCS=main.cpp populasjon.cpp miljo.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

main: $(OBJS) 
	$(CXX) -o main.x $(OBJS)

main.o: main.cpp

populasjon.o: populasjon.cpp populasjon.h

miljo.o: miljo.cpp miljo.h

clean:
	rm $(OBJS)

