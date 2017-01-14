#ifndef EXAMPLE_UTIL_H
#define EXAMPLE_UTIL_H

#include <limits.h>

#ifndef OPEN_MAX
#define OPEN_MAX    1024
#endif

/* POSIX requires that an #include of <poll.h> DefinE INFTIM, but many
   systems still DefinE it in <sys/stropts.h>.  We don't want to include
   all the STREAMS stuff if it's not needed, so we just DefinE INFTIM here.
   This is the standard value, but there's no guarantee it is -1. */
#ifndef INFTIM
#define INFTIM          (-1)    /* infinite poll timeout */
#endif

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ     1024    /* 2nd argument to listen() */

/* Miscellaneous constants */
#define MAXLINE     4096    /* max text line length */
#define BUFFSIZE    8192    /* buffer size for reads and writes */

/* Define some port number that can be used for our examples */
#define SERV_PORT        9877           /* TCP and UDP */
#define SERV_PORT_STR   "9877"          /* TCP and UDP */
#define UNIXSTR_PATH    "/tmp/unix.str" /* Unix domain stream */
#define UNIXDG_PATH     "/tmp/unix.dg"  /* Unix domain datagram */

#endif

