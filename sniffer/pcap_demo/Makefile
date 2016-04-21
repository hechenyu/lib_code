# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../lib
LDFLAGS = -lsnf -lpcap
LDPATH = -L../

PROGS =	lookupdev open_live loop setfilter findalldevs open_offline

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

open_live: open_live.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

loop: loop.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

setfilter: setfilter.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

findalldevs: findalldevs.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

open_offline: open_offline.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

