CXX=g++
CXXFLAGS=-Wall -std=c++11

SUBDIRS = build wavefunctions

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

main: $(OBJS) 
	$(CXX) -o main.x $(wildcard $(SUBDIRS)/*.o)

main.o: main.cpp

clean: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ clean

.PHONY: subdirs $(SUBDIRS)
.PHONY: all clean
