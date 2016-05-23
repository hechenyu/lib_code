# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = -I../libsnf -I../libptl
LDFLAGS = -lptl -lsnf -lnet -lpcap
LDPATH = -L..

PROGS =	http200_cheat

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

http200_cheat: http200_cheat.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

