RM = rm -f
CC = gcc
INCLUDE = -I../../lib/
CFLAGS = -Wall -g -O2 ${INCLUDE}
LIBS = ../../lib/libunpipc.a -lpthread -lrt

PROGS =	test1 testcancel incr_rwlock1

all:	${PROGS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

testcancel:	testcancel.o
		${CC} ${CFLAGS} -o $@ testcancel.o ${LIBS}

incr_rwlock1:	incr_rwlock1.o
		${CC} ${CFLAGS} -o $@ incr_rwlock1.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES} *.o
