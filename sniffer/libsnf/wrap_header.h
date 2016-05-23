#ifndef	__snf_wrap_header_h
#define	__snf_wrap_header_h

#ifdef USE_LIBNET_HEADERS
#include <libnet.h>

typedef struct libnet_ether_header Ether_header;
typedef struct libnet_ipv4_header Ipv4_header;
typedef struct libnet_tcp_header Tcp_header;
typedef struct libnet_udp_header Udp_header;

#else
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

typedef struct ether_header Ether_header;
typedef struct ip Ipv4_header;
typedef struct tcphdr Tcp_header;
typedef struct udphdr Udp_header;
#endif

#endif
