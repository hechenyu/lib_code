# my makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = 
LDFLAGS = 
LDPATH = 

TARGETS = sclist_test dclist_test stl_list_test stack_test queue_test \
		  stl_stack_test stl_queue_test

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.exe *.dSYM

sclist_test: sclist_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

dclist_test: dclist_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

stl_list_test: stl_list_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

stack_test: stack_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

queue_test: queue_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

stl_stack_test: stl_stack_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

stl_queue_test: stl_queue_test.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

