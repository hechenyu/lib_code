# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../lib
LDFLAGS = -lsnf -lpcap
LDPATH = -L../

PROGS =	simplesniffer arpsniffer arpsniffer_file ipsniffer ipsniffer_bsd

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

simplesniffer: simplesniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

arpsniffer: arpsniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

arpsniffer_file: arpsniffer_file.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ipsniffer: ipsniffer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ipsniffer_bsd: ipsniffer_bsd.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)


