/*
 *
 *  libnet 1.1
 *  Build a UDP packet
 *
 *  Copyright (c) 1998 - 2004 Mike D. Schiffman <mike@infonexus.com>
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

void usage(char *name);

int main(int argc, char *argv[])
{
	int c, i, j, build_ip;
	char *cp;
	libnet_t *l;
	libnet_ptag_t ip, ipo;
	libnet_ptag_t udp;
	char *payload;
	u_short payload_s;
	struct libnet_stats ls;
	u_long src_ip, dst_ip;
	u_short src_prt, dst_prt;
	u_char opt[20];

	printf("libnet 1.1 packet shaping: UDP + IP options[raw]\n"); 

	/*
	 *  Initialize the library.  Root priviledges are required.
	 */
	l = Libnet_init(
			LIBNET_RAW4,                            /* injection type */
			NULL);                                  /* network interface */

	src_ip  = 0;
	dst_ip  = 0;
	src_prt = 0;
	dst_prt = 0;
	payload = NULL;
	payload_s = 0;
	ip = ipo = udp = 0;
	while ((c = getopt(argc, argv, "d:s:p:")) != EOF)
	{
		switch (c)
		{
			/*
			 *  We expect the input to be of the form `ip.ip.ip.ip.port`.  We
			 *  point cp to the last dot of the IP address/port string and
			 *  then seperate them with a NULL byte.  The optarg now points to
			 *  just the IP address, and cp points to the port.
			 */
			case 'd':
				if (!(cp = strrchr(optarg, '.')))
				{
					usage(argv[0]);
				}
				*cp++ = 0;
				dst_prt = (u_short)atoi(cp);
				dst_ip = Libnet_name2addr4(l, optarg, LIBNET_RESOLVE);
				break;
			case 's':
				if (!(cp = strrchr(optarg, '.')))
				{
					usage(argv[0]);
				}
				*cp++ = 0;
				src_prt = (u_short)atoi(cp);
				src_ip = Libnet_name2addr4(l, optarg, LIBNET_RESOLVE);
				break;
			case 'p':
				payload = optarg;
				payload_s = strlen(payload);
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}

	if (!src_ip || !src_prt || !dst_ip || !dst_prt)
	{
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	for (build_ip = 0, i = 0; i < 10; i++)
	{
		udp = Libnet_build_udp(
				src_prt,                                /* source port */
				dst_prt + i,                            /* destination port */
				LIBNET_UDP_H + payload_s,               /* packet length */
				0,                                      /* checksum */
				(uint8_t*)payload,                     /* payload */
				payload_s,                              /* payload size */
				l,                                      /* libnet handle */
				udp);                                   /* libnet id */

		if (1)
		{
			build_ip = 0;
			/* this is not a legal options string */
			for (j = 0; j < 20; j++)
			{
				opt[j] = libnet_get_prand(LIBNET_PR2);
			}
			ipo = Libnet_build_ipv4_options(
					opt,
					20,
					l,
					ipo);

			ip = Libnet_build_ipv4(
					LIBNET_IPV4_H + 20 + payload_s + LIBNET_UDP_H, /* length */
					0,                                          /* TOS */
					242,                                        /* IP ID */
					0,                                          /* IP Frag */
					64,                                         /* TTL */
					IPPROTO_UDP,                                /* protocol */
					0,                                          /* checksum */
					src_ip,
					dst_ip,
					NULL,                                       /* payload */
					0,                                          /* payload size */
					l,                                          /* libnet handle */
					ip);                                        /* libnet id */
		}

		/*
		 *  Write it to the wire.
		 */
		fprintf(stderr, "%d byte packet, ready to go\n",
				libnet_getpacket_size(l));
		c = Libnet_write(l);
	}
	libnet_stats(l, &ls);
	fprintf(stderr, "Packets sent:  %lld\n"
			"Packet errors: %lld\n"
			"Bytes written: %lld\n",
			(long long)ls.packets_sent, (long long)ls.packet_errors,
			(long long)ls.bytes_written);
	libnet_destroy(l);
	return (EXIT_SUCCESS);
}

void usage(char *name)
{
	fprintf(stderr,
			"usage: %s -s source_ip.source_port -d destination_ip.destination_port"
			" [-p payload]\n",
			name);
}
/* EOF */
