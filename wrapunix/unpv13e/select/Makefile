RM = rm -f
CC = gcc
CFLAGS = -Wall -g -I../lib -O2
INCLUDE = -I../lib/
LIBS = ../libunp.a -lpthread

PROGS =	tcpcli01 tcpcli02 tcpcli03

all:	${PROGS}

tcpcli01:	tcpcli01.o strcliselect01.o
		${CC} ${CFLAGS} -o $@ tcpcli01.o strcliselect01.o ${LIBS}

tcpcli02:	tcpcli02.o strcliselect02.o
		${CC} ${CFLAGS} -o $@ tcpcli02.o strcliselect02.o ${LIBS}

tcpcli03:	tcpcli03.o
		${CC} ${CFLAGS} -o $@ tcpcli03.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES} *.o
