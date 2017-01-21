# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 
INCLUDE = 
LDFLAGS = -pthread
LDPATH = 

PROGS =	task_queue thread_test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

task_queue: task_queue.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

thread_test: thread_test.o thread.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

