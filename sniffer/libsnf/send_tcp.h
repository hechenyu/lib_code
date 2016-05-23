#include <libnet.h>

#ifndef MAX_SEND_LEN
#define MAX_SEND_LEN    1400
#endif

void Send_tcp_resp(const char *data, int len,
	struct libnet_tcp_hdr *tcpptr, struct libnet_ipv4_hdr *ipptr, struct libnet_ethernet_hdr *eptr,
	libnet_t *l);
