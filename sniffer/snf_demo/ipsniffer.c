/* Simple ARP sniffer
 * To compile: gcc ipsniffer.c -o ipsniffer -lpcap
 * Run as root!
 * */
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>

#include "snf.h"

#define MAXBYTES2CAPTURE 2048
int main(int argc, char *argv[])
{
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	pcap_t *descr = NULL;
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct iphdr *ipptr = NULL;
	struct in_addr addr;

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

	descr = Pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1, 512);
	Pcap_lookupnet(argv[1], &netaddr, &mask);
	Pcap_compile(descr, &filter, "ip", 1, mask);
	Pcap_setfilter(descr, &filter);
	while (1){
		Pcap_next_ex(descr, &pkthdr, &packet);
        if (packet == NULL) {
            continue;
        }
		ipptr = (struct iphdr *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf("\n\nthe IP packets version: %d\n", ipptr->version); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->tot_len));
		printf ("the IP protocol is %d\n", ipptr->protocol);
		addr.s_addr = ipptr->daddr;
		printf ("Destination IP: %s\n", inet_ntoa(addr));    
		addr.s_addr = ipptr->saddr;
		printf ("Source IP: %s\n", inet_ntoa(addr));
	}
	return 0;
}
