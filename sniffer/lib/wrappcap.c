#include "wrappcap.h"
#include "error.h"

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

