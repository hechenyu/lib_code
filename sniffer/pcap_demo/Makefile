# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../libsnf
LDFLAGS = -lsnf -lpcap
LDPATH = -L..

PROGS =	lookupdev open_live loop setfilter findalldevs open_offline \
		simplesniffer arpsniffer ipsniffer ipsniffer_bsd udpsniffer udpsniffer_bsd tcpsniffer tcpsniffer_bsd

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

simplesniffer: simplesniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

arpsniffer: arpsniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ipsniffer: ipsniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ipsniffer_bsd: ipsniffer_bsd.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

udpsniffer: udpsniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

udpsniffer_bsd: udpsniffer_bsd.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcpsniffer: tcpsniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcpsniffer_bsd: tcpsniffer_bsd.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

