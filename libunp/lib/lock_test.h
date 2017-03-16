#ifndef __unp_lock_test_h
#define __unp_lock_test_h

#include <fcntl.h>
#include "error.h"

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len);
pid_t Lock_test(int fd, int type, off_t offset, int whence, off_t len);

#endif

