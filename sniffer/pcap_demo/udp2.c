/* Simple TCP sniffer
 * To compile: gcc udpsniffer.c -o udppsniffer -lpcap
 * Run as root!
 * */
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#include "wrap_pcap.h"

#define MAXBYTES2CAPTURE 2048

int main(int argc, char *argv[])
{
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	pcap_t *descr = NULL;
	struct pcap_pkthdr pkthdr;
	const unsigned char *packet = NULL;
	struct ip *ipptr = NULL;
	struct udphdr *udpptr = NULL;

	if (argc < 2 || argc > 3 || (argv[1][0] == '-' && argv[1][1] == 'h')){
		printf("Usage: udpsniffer <interface> | udpsniffer -f <dumpfile>\n");
		exit(1);
	}

    if (argc == 2) {
	    descr = Pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1, 512);
	    Pcap_lookupnet(argv[1], &netaddr, &mask);
    } else {    // argc == 3
	    descr = Pcap_open_offline(argv[2]);
    }
	Pcap_compile(descr, &filter, "udp", 1, mask);
	Pcap_setfilter(descr, &filter);

	while (1){
		packet = Pcap_next(descr, &pkthdr);
		if (packet == NULL) {
            if (pcap_file(descr) != NULL) {
                printf("\nend of dumpfile!\n");
            } else {
                printf("\n loop was broken out of with pcap_breakloop!\n");
            }
            exit(1);
        }

		ipptr = (struct ip *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr.len);
		printf("\n\nthe IP packets version: %d\n", ipptr->ip_v); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->ip_len));
		printf ("the IP protocol is %d\n", ipptr->ip_p);
		printf ("Destination IP: %s\n", inet_ntoa(ipptr->ip_dst));    
		printf ("Source IP: %s\n", inet_ntoa(ipptr->ip_src));

		udpptr = (struct udphdr *) (packet + 14 + ipptr->ip_hl*4);
		printf ("Destination port : %d\n", ntohs(udpptr->uh_dport));
		printf ("Source port : %d\n", ntohs(udpptr->uh_sport));
		printf ("the len of udp packet is %u\n", ntohs(udpptr->uh_ulen));
	}
	return 0;
}
