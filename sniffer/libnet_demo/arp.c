/*
 *
 *  libnet 1.1
 *  Build an ARP packet
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

int main(int argc, char *argv[])
{
	int c;
	uint32_t i;
	libnet_t *l;
	libnet_ptag_t t;
	char *device = NULL;
	uint8_t *packet;
	uint32_t packet_s;
	u_char enet_src[6] = {0x0d, 0x0e, 0x0a, 0x0d, 0x00, 0x00};
	u_char enet_dst[6] = {0x00, 0x10, 0x67, 0x00, 0xb1, 0x86};

	printf("libnet 1.1 packet shaping: ARP[link -- autobuilding ethernet]\n"); 

	if (argc > 1)
	{
		device = argv[1];
	}

	l = Libnet_init(
			LIBNET_LINK_ADV,                        /* injection type */
			device);                                /* network interface */

	i = Libnet_get_ipaddr4(l);

	t = Libnet_build_arp(
			ARPHRD_ETHER,                           /* hardware addr */
			ETHERTYPE_IP,                           /* protocol addr */
			6,                                      /* hardware addr size */
			4,                                      /* protocol addr size */
			ARPOP_REPLY,                            /* operation type */
			enet_src,                               /* sender hardware addr */
			(uint8_t *)&i,                         /* sender protocol addr */
			enet_dst,                               /* target hardware addr */
			(uint8_t *)&i,                         /* target protocol addr */
			NULL,                                   /* payload */
			0,                                      /* payload size */
			l,                                      /* libnet context */
			0);                                     /* libnet id */

	t = Libnet_autobuild_ethernet(
			enet_dst,                               /* ethernet destination */
			ETHERTYPE_ARP,                          /* protocol type */
			l);                                     /* libnet handle */

	Libnet_adv_cull_packet(l, &packet, &packet_s);
	fprintf(stderr, "packet size: %d\n", packet_s);
	libnet_adv_free_packet(l, packet);

	c = Libnet_write(l);
	fprintf(stderr, "Wrote %d byte ARP packet from context \"%s\"; "
			"check the wire.\n", c, libnet_cq_getlabel(l));

	libnet_destroy(l);
	return (EXIT_SUCCESS);
}

/* EOF */
