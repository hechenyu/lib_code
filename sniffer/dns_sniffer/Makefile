# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = -I../libsnf -I../libptl
LDFLAGS = -lptl -lsnf -lpcap
LDPATH = -L..

PROGS =	dns_sniffer dns_sniffer_bsd

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

dns_sniffer_bsd: dns_sniffer_bsd.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
