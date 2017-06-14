#ifndef __unp_dg_echo_h
#define __unp_dg_echo_h

#include "wrapsock.h"
#include "wrapstdio.h"
#include "sock_ntop.h"

#ifdef  __cplusplus
extern "C" {
#endif

void    dg_echo(int, SA *, socklen_t);

#ifdef  __cplusplus
}   // extern "C"
#endif

#endif
