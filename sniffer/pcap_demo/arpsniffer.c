/* Simple ARP sniffer
 * To compile: gcc arpsniffer.c -o arpsniff -lpcap
 * Run as root!
 * */
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "wrap_pcap.h"

//ARP Header, (assuming Ethernet+ipv4)
#define ARP_REQUEST 1
#define ARP_REPLY 2

typedef struct arphdr {
	u_int16_t htype; //hardware type
	u_int16_t ptype; //protocol type
	u_char hlen; //hardware address length
	u_char plen; //protocol address length
	u_int16_t oper; //operation code
	u_char sha[6]; //sender hardware address
	u_char spa[4]; //sender ip address
	u_char tha[6]; //target hardware address
	u_char tpa[4]; //target ip address
} arphdr_t;

#define MAXBYTES2CAPTURE 2048

int main(int argc, char *argv[])
{
	int i=0;
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	pcap_t *descr = NULL;
	struct pcap_pkthdr pkthdr;
	const unsigned char *packet = NULL;
	arphdr_t *arpheader = NULL;

	if (argc < 2 || argc > 3 || (argv[1][0] == '-' && argv[1][1] == 'h')){
		printf("Usage: arpsniffer <interface> | arpsniffer -f <dumpfile>\n");
		exit(1);
	}

    if (argc == 2) {
	    descr = Pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1, 512);
	    Pcap_lookupnet(argv[1], &netaddr, &mask);
    } else {    // argc == 3
	    descr = Pcap_open_offline(argv[2]);
    }
	Pcap_compile(descr, &filter, "arp", 1, mask);
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

		arpheader = (struct arphdr *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr.len);
		printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ?
			"Ethernet" : "Unknown");
		printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ?
			"Ethernet" : "Unknown");
		printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST) ?
				"ARP Request" : "ARP Reply");
		if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x0800) {
			printf("Sender MAC: ");
			for (i=0; i<6; i++) printf("%02x:", arpheader->sha[i]);
			printf("\nSender IP: ");
			for (i=0; i<4; i++) printf("%d.", arpheader->spa[i]);
			printf("\nTarget MAC: ");
			for (i=0; i<6; i++) printf("%02x:", arpheader->tha[i]);
			printf("\nTarget IP: ");
			for (i=0; i<4; i++) printf("%d.", arpheader->tpa[i]);
			printf("\n");
		}
	}
	return 0;
}
