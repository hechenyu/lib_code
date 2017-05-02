#ifndef __unp_lock_reg_h
#define __unp_lock_reg_h

#include <fcntl.h>
#include "error.h"

int     lock_reg(int, int, int, off_t, int, off_t);
void    Lock_reg(int, int, int, off_t, int, off_t);

#endif

