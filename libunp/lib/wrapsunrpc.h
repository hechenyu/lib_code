#ifndef __unp_wrapsunrpc_h
#define __unp_wrapsunrpc_h

#include <rpc/rpc.h>
#include "error.h"

CLIENT *Clnt_create(const char *, u_long, u_long, const char *);
void    Clnt_control(CLIENT *, u_int, char *);

#endif

