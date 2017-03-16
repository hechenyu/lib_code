#ifndef __unp_lock_reg_h
#define __unp_lock_reg_h

#include <fcntl.h>
#include "error.h"

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
void Lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);

#endif

