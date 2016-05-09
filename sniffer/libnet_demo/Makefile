# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../libsnf
LDFLAGS = -lsnf -lnet
LDPATH = -L..

PROGS =	ip_link ip_raw tcp1 tcp2 udp1 udp2

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

ip_link: ip_link.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

ip_raw: ip_raw.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcp1: tcp1.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcp2: tcp2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

udp1: udp1.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

udp2: udp2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

