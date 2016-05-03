CC = gcc
CFLAGS = -I. -g -O2 -D_REENTRANT -Wall  -I../libutl #`libnet-config --defines`
RANLIB = ranlib

# Following is the main library, built from all the object files
# in the lib/ and libfree/ directories.
LIBSNF_NAME = ../libinj.a

# Following are all the object files to create in the lib/ directory.
LIB_OBJS = wraplibnet.o
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
