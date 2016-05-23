CC = gcc
CFLAGS = -I. -g -O2 -D_REENTRANT -Wall -I../libutl
RANLIB = ranlib

# Following is the main library, built from all the object files
# in the lib/ and libfree/ directories.
LIBSNF_NAME = ../libsnf.a

# Following are all the object files to create in the lib/ directory.
LIB_OBJS = error.o wrap_pcap.o wrap_libnet.o send_tcp.o
#LIB_SRCS = $(shell ls *.c)
#LIB_OBJS = $(LIB_SRCS:%.c=%.o)

PROGS = ${LIBSNF_NAME}

CLEANFILES = core core.* *.core *.o temp.* *.out typescript* \
		*.lc *.lh *.bsdi *.sparc *.uw

all:	${LIB_OBJS}
		ar rv ${LIBSNF_NAME} $?
		${RANLIB} ${LIBSNF_NAME}

clean:
		rm -f ${PROGS} ${CLEANFILES}
