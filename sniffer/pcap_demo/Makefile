# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../lib
LDFLAGS = -lsnf -lpcap
LDPATH = -L../

PROGS =	lookupdev

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

lookupdev: lookupdev.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)


