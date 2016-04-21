#ifndef	__unp_error_h
#define __unp_error_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#ifndef MAXLINE
#define	MAXLINE		4096	/* max text line length */
#endif

#ifndef	HAVE_VSNPRINTF
#define HAVE_VSNPRINTF
#endif

#ifdef __cplusplus
extern "C" {
#endif

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

#ifdef __cplusplus
}
#endif

#endif

