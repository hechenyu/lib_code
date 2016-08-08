# my makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = 
LDFLAGS = 
LDPATH = 

TARGETS = slist_test dlist_test

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.exe *.dSYM

slist_test: slist_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

dlist_test: dlist_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

