/*
 *
 * libnet 1.1
 * Build a IPv4 packet with what you want as payload
 *
 * Copyright (c) 2003 Frédéric Raynal <pappy@security-labs.org>
 * All rights reserved.
 *
 * Ex:
 * - send an UDP packet from port 4369 to port 8738
 *    ./ip -s 1.1.1.1 -d 2.2.2.2
 *
 * - send a TCP SYN from port 4369 to port 8738
 *   ./ip -s 1.1.1.1 -d 2.2.2.2 -t -p `printf "\x04\x57\x08\xae\x01\x01\x01\x01\x02\x02\x02\x02\x50\x02\x7f\xff\xd5\x91\x41\x41"`
 *
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
	int c;
	libnet_t *l;
	char *device = NULL;
	char *dst = "2.2.2.2", *src = "1.1.1.1";
	u_long src_ip, dst_ip;
	u_short proto = IPPROTO_UDP;
	u_char payload[255] = {0x11, 0x11, 0x22, 0x22, 0x00, 0x08, 0xc6, 0xa5};
	u_long payload_s = 8;

	printf("libnet 1.1 packet shaping: IP + payload[raw]\n");

	/*
	 * handle options
	 */ 
	while ((c = getopt(argc, argv, "d:s:tp:i:h")) != EOF)
	{
		switch (c)
		{
			case 'd':
				dst = optarg;
				break;

			case 's':
				src = optarg;
				break;

			case 'i':
				device = optarg;
				break;

			case 't':
				proto = IPPROTO_TCP;
				break;

			case 'p':
				strncpy((char *)payload, optarg, sizeof(payload)-1);
				payload_s = strlen((char *)payload);
				break;

			case 'h':
				usage(argv[0]);
				exit(EXIT_SUCCESS);

			default:
				exit(EXIT_FAILURE);
		}
	}

	if (device == NULL) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/*
	 *  Initialize the library.  Root priviledges are required.
	 */
	l = Libnet_init(
			LIBNET_RAW4,                            /* injection type */
			device);                                /* network interface */

	printf("Using device %s\n", l->device);

	dst_ip = Libnet_name2addr4(l, dst, LIBNET_RESOLVE);
	src_ip = Libnet_name2addr4(l, src, LIBNET_RESOLVE);

	/*
	 * Build the packet
	 */ 
	Libnet_build_ipv4(
			LIBNET_IPV4_H + payload_s,                  /* length */
			0,                                          /* TOS */
			242,                                        /* IP ID */
			0,                                          /* IP Frag */
			64,                                         /* TTL */
			proto,                                      /* protocol */
			0,                                          /* checksum */
			src_ip,                                     /* source IP */
			dst_ip,                                     /* destination IP */
			payload,                                    /* payload */
			payload_s,                                  /* payload size */
			l,                                          /* libnet handle */
			0);                                         /* libnet id */

	/*
	 *  Write it to the wire.
	 */
	c = Libnet_write(l);
	fprintf(stderr, "Wrote %d byte IP packet; check the wire.\n", c);

	libnet_destroy(l);
	return (EXIT_SUCCESS);
}

void usage(char *name)
{
	fprintf(stderr,
			"usage: %s [-s source_ip] [-d destination_ip]"
			" [-i iface] [-p payload] [-t]\n",
			name);
}

/* EOF */
