# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I../libinj
LDFLAGS = -linj -lutl -lnet
LDPATH = -L..

PROGS =	sendip sendip_raw4

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

sendip: sendip.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

sendip_raw4: sendip_raw4.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

