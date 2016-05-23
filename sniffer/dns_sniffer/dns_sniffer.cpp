/* Simple TCP sniffer
 * To compile: gcc udpsniffer.c -o udppsniffer -lpcap
 * Run as root!
 * */
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <libnet.h>
#include <string>

#include "snf.h"
#include "ptl.h"

using std::string;

using namespace ptl;

#define MAXBYTES2CAPTURE 2048

int main(int argc, char *argv[])
{
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	pcap_t *descr = NULL;
	struct pcap_pkthdr pkthdr;
	const unsigned char *packet = NULL;
	Ipv4_header *ipptr = NULL;
	Udp_header *udpptr = NULL;
	Dns_header *dnsptr = NULL;
    Dns_question dnsqry;

	if (argc < 2 || argc > 3 || (argv[1][0] == '-' && argv[1][1] == 'h')){
		printf("Usage: httpreq_sniffer <interface> | httpreq_sniffer -f <dumpfile>\n");
		exit(1);
	}

    if (argc == 2) {
	    descr = Pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1, 512);
	    Pcap_lookupnet(argv[1], &netaddr, &mask);
    } else {    // argc == 3
	    descr = Pcap_open_offline(argv[2]);
    }
	Pcap_compile(descr, &filter, (char *) "udp and port 53", 1, mask);
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

		ipptr = (Ipv4_header *)(packet + 14);
		printf ("\n\nReceived Packet Size: %d bytes\n", pkthdr.len);
		printf ("\n\nthe IP packets version: %d\n", ipptr->ip_v); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->ip_len));
		printf ("the IP protocol is %d\n", ipptr->ip_p);
		printf ("Destination IP: %s\n", inet_ntoa(ipptr->ip_dst));    
		printf ("Source IP: %s\n", inet_ntoa(ipptr->ip_src));

		udpptr = (Udp_header *) (packet + 14 + ipptr->ip_hl*4);
		printf ("Destination port : %d\n", ntohs(udpptr->uh_dport));
		printf ("Source port : %d\n", ntohs(udpptr->uh_sport));
		printf ("the len of udp packet is %u\n", ntohs(udpptr->uh_ulen));

		dnsptr = (Dns_header *) (packet + 14 + ipptr->ip_hl*4 + sizeof (libnet_udp_hdr));
		printf ("the Dns transaction id: %x\n", ntohs(dnsptr->id));
		printf ("the Dns flags: %x\n", ntohs(dnsptr->flags));
		printf ("the Dns questions: %d\n", ntohs(dnsptr->num_q));
		printf ("the Dns Answer RRs: %d\n", ntohs(dnsptr->num_answ_rr));
		printf ("the Dns Authority RRs: %d\n", ntohs(dnsptr->num_auth_rr));
		printf ("the Dns Additional RRs: %d\n", ntohs(dnsptr->num_addi_rr));

		if (ntohs(dnsptr->num_q) != 1)
			continue;

        uint8_t *dns_body = (uint8_t *) (packet + 14 + ipptr->ip_hl*4 +
                sizeof (Udp_header) + sizeof (Dns_header));
        int ret = parser_dns_query(dns_body, packet+pkthdr.caplen, dnsqry);
        if (ret < 0) {
            printf ("parser dns question error!\n");
            continue;
        }
		printf ("the Dns query: %s\n", dnsqry.qname.c_str());
		printf ("the Dns query type: %x\n", ntohs(dnsqry.qtype));
		printf ("the Dns query class: %x\n", ntohs(dnsqry.qclass));
	}
	return 0;
}
