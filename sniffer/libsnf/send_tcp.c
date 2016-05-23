#include "send_tcp.h"
#include "wrap_libnet.h"

void Send_tcp_resp(const char *data, int len,
	Tcp_header *tcpptr, Ipv4_header *ipptr, Ether_header *eptr,
	libnet_t *l)
{
	int req_payload_len = ntohs(ipptr->ip_len)-ipptr->ip_hl*4-tcpptr->th_off*4;
	int nsend = 0; 
    int nleft = len;
	for (int i = 0; i < len; i += nsend, nleft -= nsend) {
		nsend = (nleft < MAX_SEND_LEN) ? nleft : MAX_SEND_LEN; 

		// 构造TCP Segment
		Libnet_build_tcp(
				ntohs(tcpptr->th_dport),               /* source port */
				ntohs(tcpptr->th_sport),               /* destination port */
				ntohl(tcpptr->th_ack)+i,               /* sequence number */
				ntohl(tcpptr->th_seq)+req_payload_len, /* acknowledgement num */
				TH_ACK | TH_PUSH | (nsend < MAX_SEND_LEN ? TH_FIN : 0), 
                                                       /* control flags */
				17520,                                 /* window size */
				0,                                     /* checksum */
				0,                                     /* urgent pointer */
				LIBNET_TCP_H + nsend,                  /* TCP packet size */
				(uint8_t *) data + i,                  /* payload */
				nsend,                                 /* payload size */
				l,                                     /* libnet handle */
				0);                                    /* libnet id */

		// 构造IP datagram
		Libnet_build_ipv4(
				LIBNET_IPV4_H + LIBNET_TCP_H + nsend,  /* length */
				0,                                     /* TOS */
				1691,                                  /* IP ID */
				0,                                     /* IP Frag */
				64,                                    /* TTL */
				IPPROTO_TCP,                           /* protocol */
				0,                                     /* checksum */
				ipptr->ip_dst.s_addr,                  /* source IP */
				ipptr->ip_src.s_addr,                  /* destination IP */
				NULL,                                  /* payload */
				0,                                     /* payload size */
				l,                                     /* libnet handle */
				0);                                    /* libnet id */

		// 构造Ether Frame
        if (eptr) {
		    Libnet_build_ethernet(
				    eptr->ether_shost,                  /* ethernet destination */
				    eptr->ether_dhost,                  /* ethernet source */
				    ETHERTYPE_IP,                       /* protocol type */
				    NULL,                               /* payload */
				    0,                                  /* payload size */
				    l,                                  /* libnet handle */
				    0);                                 /* libnet id */
        }

		// 发送报文
		/*
		 *  Write it to the wire.
		 */
		int c = Libnet_write(l);
		printf("Wrote %d byte TCP packet; check the wire.\n", c);

		// 为下一个报文做准备
		libnet_clear_packet(l);
	}
}

