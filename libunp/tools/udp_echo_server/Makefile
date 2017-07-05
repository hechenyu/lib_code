# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DHAVE_EPOLL
INCLUDE = -I../../lib
LDFLAGS = ../../lib/libunp.a -lpthread -lrt
LDPATH = 

PROGS =	udpserv01

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

udpserv01: udpserv01.o dg_echo.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)



