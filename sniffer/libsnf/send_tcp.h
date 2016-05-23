#ifndef	__snf_send_tcp_h
#define	__snf_send_tcp_h

#include <libnet.h>

#include "wrap_header.h"

#ifndef MAX_SEND_LEN
#define MAX_SEND_LEN    1400
#endif

#ifdef __cplusplus
extern "C" {
#endif

void Send_tcp_resp(const char *data, int len,
	Tcp_header *tcpptr, Ipv4_header *ipptr, Ether_header *eptr,
	libnet_t *l);

#ifdef __cplusplus
}
#endif

#endif
