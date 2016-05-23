CXX = g++
CXXFLAGS = -I. -g -O2 -D_REENTRANT -Wall -DNDEBUG
RANLIB = ranlib

# Following is the main library, built from all the object files
# in the lib/ and libfree/ directories.
LIBSNF_NAME = ../libptl.a

# Following are all the object files to create in the lib/ directory.
LIB_OBJS = http_parser.o httpreq.o httpresp.o dns_parser.o http_builder.o
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
