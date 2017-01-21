# my makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DNDEBUG
INCLUDE = 
LDFLAGS = 
LDPATH = 

TARGETS = bstree_test rbtree_test

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.exe *.dSYM

bstree_test: bstree_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

rbtree_test: rbtree_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

