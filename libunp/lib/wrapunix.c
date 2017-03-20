/*
 * Socket wrapper functions.
 * These could all go into separate files, so only the ones needed cause
 * the corresponding function to be added to the executable.  If sockets
 * are a library (SVR4) this might make a difference (?), but if sockets
 * are in the kernel (BSD) it doesn't matter.
 *
 * These wrapper functions also use the same prototypes as POSIX.1g,
 * which might differ from many implementations (i.e., POSIX.1g specifies
 * the fourth argument to getsockopt() as "void *", not "char *").
 *
 * If your system's headers are not correct [i.e., the Solaris 2.5
 * <sys/socket.h> omits the "const" from the second argument to both
 * bind() and connect()], you'll get warnings of the form:
 *warning: passing arg 2 of `bind' discards `const' from pointer target type
 *warning: passing arg 2 of `connect' discards `const' from pointer target type
 */

#include	"wrapunix.h"

void *
Calloc(size_t n, size_t size)
{
	void	*ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}

void
Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}

void
Dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		err_sys("dup2 error");
}

#ifdef	HAVE_FATTACH
void
Fattach(int fd, const char *path)
{
	if (fattach(fd, path) == -1)
		err_sys("fattach error");
}
#endif

int 
Fcntl(int fd, int cmd, ...)
{
    va_list ap;
    int iarg;
    void *varg;
    int n;

    va_start(ap, cmd);
    if (cmd == F_SETLKW || cmd == F_SETLK) {
        varg = va_arg(ap, void *);
        n = fcntl(fd, cmd, varg);
    } else {
        iarg = va_arg(ap, int);
        n = fcntl(fd, cmd, iarg);
    }
    va_end(ap);

    if (n == -1) {
		err_sys("fcntl error");
    }
    return(n);
}

pid_t
Fork(void)
{
	pid_t	pid;

	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return(pid);
}

long
Fpathconf(int fd, int name)
{
	long	val;

	errno = 0;		/* in case fpathconf() does not change this */
	if ( (val = fpathconf(fd, name)) == -1) {
		if (errno != 0)
			err_sys("fpathconf error");
		else
			err_sys("fpathconf: %d not defined", name);
	}
	return(val);
}

void
Fstat(int fd, struct stat *ptr)
{
	if (fstat(fd, ptr) == -1)
		err_sys("fstat error");
}

#ifdef	HAVE_SYS_IPC_H
key_t
Ftok(const char *pathname, int id)
{
	key_t	key;

	if ( (key = ftok(pathname, id)) == -1)
		err_sys("ftok error for pathname \"%s\" and id %d", pathname, id);
	return(key);
}
#endif	/* HAVE_SYS_IPC_H */

void
Ftruncate(int fd, off_t length)
{
	if (ftruncate(fd, length) == -1)
		err_sys("ftruncate error");
}

int
Getopt(int argc, char *const *argv, const char *str)
{
	int		opt;

	if ( ( opt = getopt(argc, argv, str)) == '?')
		exit(1);		/* getopt() has already written to stderr */
	return(opt);
}

void
Gettimeofday(struct timeval *tv, void *foo)
{
	if (gettimeofday(tv, foo) == -1)
		err_sys("gettimeofday error");
	return;
}

int
Ioctl(int fd, int request, void *arg)
{
	int		n;

	if ( (n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");
	return(n);	/* streamio of I_LIST returns value */
}

void
Kill(pid_t pid, int signo)
{
	if (kill(pid, signo) == -1)
		err_sys("kill error");
}

off_t
Lseek(int fd, off_t offset, int whence)
{
	off_t	pos;

	if ( (pos = lseek(fd, offset, whence)) == (off_t) -1)
		err_sys("lseek error");
	return(pos);
}

void *
Malloc(size_t size)
{
	void	*ptr;

	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return(ptr);
}

void
Mkfifo(const char *pathname, mode_t mode)
{
	if (mkfifo(pathname, mode) == -1)
		err_sys("mkfifo error for %s", pathname);
}

void
Mktemp(char *template)
{
	if (mktemp(template) == NULL || template[0] == 0)
		err_quit("mktemp error");
}

int
Mkstemp(char *template)
{
	int i;

#ifdef HAVE_MKSTEMP
	if ((i = mkstemp(template)) < 0)
		err_quit("mkstemp error");
#else
	if (mktemp(template) == NULL || template[0] == 0)
		err_quit("mktemp error");
	i = Open(template, O_CREAT | O_WRONLY, FILE_MODE);
#endif

	return i;
}

#ifdef	HAVE_SYS_MMAN_H
void *
Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void	*ptr;

	if ( (ptr = mmap(addr, len, prot, flags, fd, offset)) == MAP_FAILED)
		err_sys("mmap error");
	return(ptr);
}

void
Munmap(void *addr, size_t len)
{
	if (munmap(addr, len) == -1)
		err_sys("munmap error");
}
#endif	/* HAVE_SYS_MMAN_H */

#ifdef	HAVE_MQUEUE_H
mqd_t
Mq_open(const char *pathname, int oflag, ...)
{
	mqd_t	mqd;
	va_list	ap;
	mode_t	mode;
	struct mq_attr	*attr;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		attr = va_arg(ap, struct mq_attr *);
		if ( (mqd = mq_open(pathname, oflag, mode, attr)) == (mqd_t) -1)
			err_sys("mq_open error for %s", pathname);
		va_end(ap);
	} else {
		if ( (mqd = mq_open(pathname, oflag)) == (mqd_t) -1)
			err_sys("mq_open error for %s", pathname);
	}
	return(mqd);
}

void
Mq_close(mqd_t mqd)
{
	if (mq_close(mqd) == -1)
		err_sys("mq_close error");
}

void
Mq_unlink(const char *pathname)
{
	if (mq_unlink(pathname) == -1)
		err_sys("mq_unlink error");
}

void
Mq_send(mqd_t mqd, const char *ptr, size_t len, unsigned int prio)
{
	if (mq_send(mqd, ptr, len, prio) == -1)
		err_sys("mq_send error");
}

ssize_t
Mq_receive(mqd_t mqd, char *ptr, size_t len, unsigned int *prio)
{
	ssize_t	n;

	if ( (n = mq_receive(mqd, ptr, len, prio)) == -1)
		err_sys("mq_receive error");
	return(n);
}

void
Mq_notify(mqd_t mqd, const struct sigevent *notification)
{
	if (mq_notify(mqd, notification) == -1)
		err_sys("mq_notify error");
}

void
Mq_getattr(mqd_t mqd, struct mq_attr *mqstat)
{
	if (mq_getattr(mqd, mqstat) == -1)
		err_sys("mq_getattr error");
}

void
Mq_setattr(mqd_t mqd, const struct mq_attr *mqstat, struct mq_attr *omqstat)
{
	if (mq_setattr(mqd, mqstat, omqstat) == -1)
		err_sys("mq_setattr error");
}
#endif	/* HAVE_MQUEUE_H */

int
Open(const char *pathname, int oflag, mode_t mode)
{
	int		fd;

	if ( (fd = open(pathname, oflag, mode)) == -1)
		err_sys("open error for %s", pathname);
	return(fd);
}

void
Pipe(int *fds)
{
	if (pipe(fds) < 0)
		err_sys("pipe error");
}

ssize_t
Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	if ( (n = read(fd, ptr, nbytes)) == -1)
		err_sys("read error");
	return(n);
}

void
Sigaddset(sigset_t *set, int signo)
{
	if (sigaddset(set, signo) == -1)
		err_sys("sigaddset error");
}

void
Sigdelset(sigset_t *set, int signo)
{
	if (sigdelset(set, signo) == -1)
		err_sys("sigdelset error");
}

void
Sigemptyset(sigset_t *set)
{
	if (sigemptyset(set) == -1)
		err_sys("sigemptyset error");
}

void
Sigfillset(sigset_t *set)
{
	if (sigfillset(set) == -1)
		err_sys("sigfillset error");
}

int
Sigismember(const sigset_t *set, int signo)
{
	int		n;

	if ( (n = sigismember(set, signo)) == -1)
		err_sys("sigismember error");
	return(n);
}

void
Sigpending(sigset_t *set)
{
	if (sigpending(set) == -1)
		err_sys("sigpending error");
}

void
Sigprocmask(int how, const sigset_t *set, sigset_t *oset)
{
	if (sigprocmask(how, set, oset) == -1)
		err_sys("sigprocmask error");
}

char *
Strdup(const char *str)
{
	char	*ptr;

	if ( (ptr = strdup(str)) == NULL)
		err_sys("strdup error");
	return(ptr);
}

long
Sysconf(int name)
{
	long	val;

	errno = 0;		/* in case sysconf() does not change this */
	if ( (val = sysconf(name)) == -1)
		err_sys("sysconf error");
	return(val);
}

#ifdef	HAVE_SYS_SYSCTL_H
void
Sysctl(int *name, u_int namelen, void *oldp, size_t *oldlenp,
	   void *newp, size_t newlen)
{
	if (sysctl(name, namelen, oldp, oldlenp, newp, newlen) == -1)
		err_sys("sysctl error");
}
#endif

void
Unlink(const char *pathname)
{
	if (unlink(pathname) == -1)
		err_sys("unlink error for %s", pathname);
}

pid_t
Wait(int *iptr)
{
	pid_t	pid;

	if ( (pid = wait(iptr)) == -1)
		err_sys("wait error");
	return(pid);
}

pid_t
Waitpid(pid_t pid, int *iptr, int options)
{
	pid_t	retpid;

	if ( (retpid = waitpid(pid, iptr, options)) == -1)
		err_sys("waitpid error");
	return(retpid);
}

void
Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}
