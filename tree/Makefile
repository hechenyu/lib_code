# my makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DNDEBUG
INCLUDE = 
LDFLAGS = 
LDPATH = 

TARGETS = rbtree_test

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.exe *.dSYM

rtbree_test: rbtree_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

