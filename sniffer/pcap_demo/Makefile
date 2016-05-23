# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../libsnf
LDFLAGS = -lsnf -lpcap
LDPATH = -L..

PROGS =	lookupdev open_live loop setfilter findalldevs open_offline \
		simple arp ip ip2 udp udp2 tcp tcp2

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

simple: simple.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

arp: arp.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ip: ip.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ip2: ip2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

udp: udp.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

udp2: udp2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcp: tcp.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcp2: tcp2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

