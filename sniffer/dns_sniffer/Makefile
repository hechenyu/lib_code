# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = -I../libsnf -I../libptl
LDFLAGS = -lptl -lsnf -lpcap
LDPATH = -L..

PROGS =	dns_sniffer 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

dns_sniffer: dns_sniffer.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

