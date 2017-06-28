# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DHAVE_EPOLL
INCLUDE = -I../../lib
LDFLAGS = ../../lib/libunp.a -lpthread -lrt
LDPATH = 

PROGS =	tcpechoserver tcpcheckserver

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

tcpcheckserver: tcpcheckserver.o tcpserver.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


