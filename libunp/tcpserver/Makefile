# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I../lib
LDFLAGS =
LDPATH = 

PROGS =	tcpechoserver

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

tcpechoserver: tcpechoserver.o tcpserver.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


