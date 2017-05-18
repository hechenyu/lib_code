RM = rm -f
CC = gcc
INCLUDE = -I../../lib/
CFLAGS = -Wall -g -O2 ${INCLUDE} -DHAVE_SYS_MSG_H -D_GNU_SOURCE -DHAVE_SYS_IPC_H # _GNU_SOURCE for struct msgbuf in ctl.c
LIBS = ../../lib/libunp.a -lpthread -lrt

PROGS =	client_main server_main

all:	${PROGS}

client_main:	client_main.o client.o mesg_recv.o mesg_send.o
		${CC} ${CFLAGS} -o $@ client_main.o client.o \
			mesg_recv.o mesg_send.o ${LIBS}

server_main:	server_main.o server.o mesg_recv.o mesg_send.o
		${CC} ${CFLAGS} -o $@ server_main.o server.o \
			mesg_recv.o mesg_send.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES} *.o
