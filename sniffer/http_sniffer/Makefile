# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = -I../libsnf -I../libptl
LDFLAGS = -lptl -lsnf -lpcap
LDPATH = -L..

PROGS =	httpreq_sniffer httpresp_sniffer

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

httpreq_sniffer: httpreq_sniffer.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

httpresp_sniffer: httpresp_sniffer.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

