#ifndef __unp_mcast_set_loop_h
#define __unp_mcast_set_loop_h

#include <arpa/inet.h>
#include <sys/socket.h>
#include "error.h"
#include "sockfd_to_family.h"

/* Define to 1 if the system supports IPv6 */
#define IPV6    1

int mcast_set_loop(int sockfd, int onoff);
void Mcast_set_loop(int sockfd, int onoff);

#endif

