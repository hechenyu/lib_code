#ifndef __unp_wrapunix_h
#define __unp_wrapunix_h

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <mqueue.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "error.h"

#define HAVE_MKSTEMP 1
#define HAVE_SYS_IPC_H 1
#define HAVE_SYS_MMAN_H 1
#define HAVE_MQUEUE_H 1

/*
 * In our wrappers for open(), mq_open(), and sem_open() we handle the
 * optional arguments using the va_XXX() macros.  But one of the optional
 * arguments is of type "mode_t" and this breaks under BSD/OS because it
 * uses a 16-bit integer for this datatype.  But when our wrapper function
 * is called, the compiler expands the 16-bit short integer to a 32-bit
 * integer.  This breaks our call to va_arg().  All we can do is the
 * following hack.  Other systems in addition to BSD/OS might have this
 * problem too ...
 */

#ifdef  __bsdi__
#define va_mode_t   int
#else
#define va_mode_t   mode_t
#endif
/* $$.ix [va_mode_t]~datatype,~definition~of$$ */

/* prototypes for our Unix wrapper functions: see {Sec errors} */
void    *Calloc(size_t, size_t);
void     Close(int);
void     Dup2(int, int);

#ifdef HAVE_FATTACH
void     Fattach(int, const char *);
#endif

int      Fcntl(int, int, ...);
pid_t    Fork(void);
long     Fpathconf(int, int);
void     Fstat(int, struct stat *);

#ifdef HAVE_SYS_IPC_H
key_t    Ftok(const char *, int);
#endif

void     Ftruncate(int, off_t);
int      Getopt(int, char *const *, const char *);

void     Gettimeofday(struct timeval *, void *);
int      Ioctl(int, int, void *);
void     Kill(pid_t, int);
off_t    Lseek(int, off_t, int);
void    *Malloc(size_t);
void     Mkfifo(const char *, mode_t);
void     Mktemp(char *);
int      Mkstemp(char *);

#ifdef HAVE_SYS_MMAN_H
void    *Mmap(void *, size_t, int, int, int, off_t);
void     Munmap(void *, size_t);
#endif

#ifdef HAVE_MQUEUE_H
mqd_t    Mq_open(const char *, int, ...);
void     Mq_close(mqd_t);
void     Mq_unlink(const char *);
void     Mq_send(mqd_t, const char *, size_t, unsigned int);
ssize_t  Mq_receive(mqd_t, char *, size_t, unsigned int *);
void     Mq_notify(mqd_t, const struct sigevent *);
void     Mq_getattr(mqd_t, struct mq_attr *);
void     Mq_setattr(mqd_t, const struct mq_attr *, struct mq_attr *);
#endif

int      Open(const char *, int , ...);
void     Pipe(int *fds);
ssize_t  Read(int, void *, size_t);
void     Sigaddset(sigset_t *, int);
void     Sigdelset(sigset_t *, int);
void     Sigemptyset(sigset_t *);
void     Sigfillset(sigset_t *);
int      Sigismember(const sigset_t *, int);
void     Sigpending(sigset_t *);
void     Sigprocmask(int, const sigset_t *, sigset_t *);
char    *Strdup(const char *);
long     Sysconf(int);
void     Sysctl(int *, u_int, void *, size_t *, void *, size_t);
void     Unlink(const char *);
pid_t    Wait(int *);
pid_t    Waitpid(pid_t, int *, int);
void     Write(int, void *, size_t);

/* Define to 1 if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the <sys/sysctl.h> header file. */
#define HAVE_SYS_SYSCTL_H 1

#endif
