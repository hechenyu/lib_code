/*
 *
 *  libnet 1.1
 *  Build a DNSv4 packet
 *  To view: /usr/sbin/tcpdump -vvvvven -s 0 port 53
 *
 *  Copyright (c) 2003 Frédéric Raynal <pappy@security-labs.org>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wrap_libnet.h"

void usage(char *prog)
{
	fprintf(stderr, "Usage: %s -d dst_ip -q query_host [-s src_ip] [-t]\n", prog);
	exit(1);
}

int main(int argc, char *argv[])
{
	char c;
	u_long src_ip = 0, dst_ip = 0;
	u_short type = LIBNET_UDP_DNSV4_H;
	libnet_t *l;

	libnet_ptag_t ip;
	libnet_ptag_t ptag4; /* TCP or UDP ptag */
	libnet_ptag_t dns;

	char *query = NULL;
	char payload[1024];
	u_short payload_s;

	printf("libnet 1.1 packet shaping: DNSv4[raw]\n");

	/*
	 *  Initialize the library.  Root priviledges are required.
	 */
	l = Libnet_init(
			LIBNET_RAW4,                            /* injection type */
			NULL);                                  /* network interface */

	/*
	 * parse options
	 */
	while ((c = getopt(argc, argv, "d:s:q:t")) != EOF)
	{
		switch (c)
		{

			case 'd':
				dst_ip = Libnet_name2addr4(l, optarg, LIBNET_RESOLVE);
				break;
			case 's':
				src_ip = libnet_name2addr4(l, optarg, LIBNET_RESOLVE);
				break;
			case 'q':
				query = optarg;
				break;
			case 't':
				type = LIBNET_TCP_DNSV4_H;
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}

	if (!src_ip)
	{
		src_ip = Libnet_get_ipaddr4(l);
	}

	if (!dst_ip  || !query)
	{
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* 
	 * build dns payload 
	 */
	payload_s = snprintf(payload, sizeof payload, "%c%s%c%c%c%c%c", 
			(char)(strlen(query)&0xff), query, 0x00, 0x00, 0x01, 0x00, 0x01);

	/* 
	 * build packet
	 */
	dns = Libnet_build_dnsv4(
			type,          /* TCP or UDP */
			0x7777,        /* id */
			0x0100,        /* request */
			1,             /* num_q */
			0,             /* num_anws_rr */
			0,             /* num_auth_rr */
			0,             /* num_addi_rr */
			(uint8_t *)payload,
			payload_s,
			l,
			0
			);

	if (type == LIBNET_TCP_DNSV4_H) /* TCP DNS */
	{
		ptag4 = Libnet_build_tcp(
				0x6666,                                    /* source port */
				53,                                        /* destination port */
				0x01010101,                                /* sequence number */
				0x02020202,                                /* acknowledgement num */
				TH_PUSH|TH_ACK,                            /* control flags */
				32767,                                     /* window size */
				0,                                         /* checksum */
				0,                                         /* urgent pointer */
				LIBNET_TCP_H + LIBNET_TCP_DNSV4_H + payload_s, /* TCP packet size */
				NULL,                                      /* payload */
				0,                                         /* payload size */
				l,                                         /* libnet handle */
				0);                                        /* libnet id */

		ip = Libnet_build_ipv4(
				LIBNET_IPV4_H + LIBNET_TCP_H + type + payload_s,/* length */
				0,                                          /* TOS */
				242,                                        /* IP ID */
				0,                                          /* IP Frag */
				64,                                         /* TTL */
				IPPROTO_TCP,                                /* protocol */
				0,                                          /* checksum */
				src_ip,                                     /* source IP */
				dst_ip,                                     /* destination IP */
				NULL,                                       /* payload */
				0,                                          /* payload size */
				l,                                          /* libnet handle */
				0);                                         /* libnet id */
	}
	else /* UDP DNS */
	{
		ptag4 = Libnet_build_udp(
				0x6666,                                /* source port */
				53,                                    /* destination port */
				LIBNET_UDP_H + LIBNET_UDP_DNSV4_H + payload_s, /* packet length */
				0,                                      /* checksum */
				NULL,                                   /* payload */
				0,                                      /* payload size */
				l,                                      /* libnet handle */
				0);                                     /* libnet id */

		ip = Libnet_build_ipv4(
				LIBNET_IPV4_H + LIBNET_UDP_H + type + payload_s,/* length */
				0,                                          /* TOS */
				242,                                        /* IP ID */
				0,                                          /* IP Frag */
				64,                                         /* TTL */
				IPPROTO_UDP,                                /* protocol */
				0,                                          /* checksum */
				src_ip,                                     /* source IP */
				dst_ip,                                     /* destination IP */
				NULL,                                       /* payload */
				0,                                          /* payload size */
				l,                                          /* libnet handle */
				0);                                         /* libnet id */
	}

	/*
	 * write to the wire
	 */
	c = Libnet_write(l);
	fprintf(stderr, "Wrote %d byte DNS packet; check the wire.\n", c);

	libnet_destroy(l);
	return (EXIT_SUCCESS);
}
