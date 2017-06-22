# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I ../../lib
LDFLAGS = -lboost_program_options ../../lib/libunp.a -lpthread -lrt
LDPATH =

PROGS =	udp_stree_client

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

udp_stree_client: prog_opts_util.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

