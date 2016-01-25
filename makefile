CXX=g++
CXXFLAGS=-Wall -std=c++11

SUBDIRS = wavefunctions

.PHONY: subdirs $(SUBDIRS)
.PHONY: all clean

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@


#clean:	 
#$(SUBDIRS):
#	$(MAKE) -C $@ clean

