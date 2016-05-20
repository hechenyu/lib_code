#include "wrap_pcap.h"

#include <stdlib.h>

#include "error.h"

#ifndef PCAP_ERROR_BREAK 
#define PCAP_ERROR_BREAK        -2
#endif

static char pcap_errbuf[PCAP_ERRBUF_SIZE];

char *Pcap_lookupdev() 
{
    char *dev = pcap_lookupdev(pcap_errbuf);
    if (dev == NULL) {
        err_quit("pcap_lookupdev error: %s", pcap_errbuf);
    }
    return dev;
}

void Pcap_lookupnet(const char *device, bpf_u_int32 *netp, bpf_u_int32 *maskp)
{
	if (pcap_lookupnet(device, netp, maskp, pcap_errbuf) < 0) {
        err_quit("pcap_lookupnet error for %s: %s", device, pcap_errbuf);
	}
}

pcap_t *Pcap_open_live(const char *device, int snaplen, int promisc, int to_ms)
{
	pcap_t *p = pcap_open_live(device, snaplen, promisc, to_ms, pcap_errbuf);
	if (p == NULL) {
		err_quit("pcap_open_live error for %s, %d, %d, %d: %s", device, snaplen, promisc, to_ms, pcap_errbuf);
	}
	return p;
}

void Pcap_compile(pcap_t *p, struct bpf_program *fp, char *str, int optimize, bpf_u_int32 netmask)
{
    if (pcap_compile(p, fp, str, optimize, netmask) < 0) {
        err_quit("pcap_compile error for %s: %s", str, pcap_geterr(p));
    }
}

void Pcap_setfilter(pcap_t *p, struct bpf_program *fp)
{
    if (pcap_setfilter(p, fp) < 0) {
        err_quit("pcap_setfilter error: %s", pcap_geterr(p));
    }
}

pcap_t *Pcap_open_offline(const char *fname)
{
	pcap_t *p = pcap_open_offline(fname, pcap_errbuf);
	if (p == NULL) {
        err_quit("pcap_open_offline error for %s: %s", fname, pcap_errbuf);
	}
	return p;
}

const u_char *Pcap_next(pcap_t *p, struct pcap_pkthdr *h)
{
    struct pcap_pkthdr *header;
    const u_char *packet;
    int ret;
    while (1) {
        ret = pcap_next_ex(p, &header, &packet);
        if (ret > 0) {
            memcpy(h, header, sizeof(struct pcap_pkthdr));
            return packet; 
        } else if (ret < 0) {    // ret < 0
            if (ret == PCAP_ERROR_BREAK) {
                return NULL;
            } else {
                err_quit("pcap_next_ex error: %s", pcap_geterr(p));
            }
        }
        // else ret == 0, timeout and continue
    }
}

pcap_if_t *Pcap_findalldevs()
{
    pcap_if_t *alldevs = NULL;
    if (pcap_findalldevs(&alldevs, pcap_errbuf) < 0) {
        err_quit("pcap_findalldevs error: %s", pcap_errbuf);
    }
    return alldevs;
}
