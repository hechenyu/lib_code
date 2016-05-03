#include "wraplibnet.h"

#include <stdlib.h>

#include "error.h"

static char libnet_errbuf[LIBNET_ERRBUF_SIZE];

libnet_t *Libnet_init(int injection_type, const char *device)
{
    libnet_t *l = libnet_init(injection_type, device, libnet_errbuf);
    if (l == NULL) {
        err_quit("libnet_init error: %s", libnet_errbuf);
    }
    return l;
}

uint32_t Libnet_name2addr4(libnet_t *l, char *host_name, uint8_t use_name)
{
    uint32_t addr = libnet_name2addr4(l, host_name, use_name);
    if (addr == (uint32_t) -1) {
        err_quit("libnet_name2addr error for %s: %s", host_name, libnet_geterror(l));
    }
    return addr;
}

int Libnet_write(libnet_t *l)
{
    int c = libnet_write(l);
    if (c == -1) {
        err_quit("libnet_write error: %s", libnet_geterror(l));
    }
    return c;
}

libnet_ptag_t Libnet_build_ethernet(
        const uint8_t *dst, const uint8_t *src, uint16_t type, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_ethernet(
                        dst,        /* ethernet destination */
                        src,        /* ethernet source */
                        type,       /* protocol type */
                        payload,    /* payload */
                        payload_s,  /* payload size */
                        l,          /* libnet handle */
                        ptag);      /* libnet id */
    if (t == -1) {
        err_quit("libnet_build_ethernet error: %s", libnet_geterror(l));
    }
    return t;
}

libnet_ptag_t Libnet_build_ipv4(uint16_t ip_len, uint8_t tos, uint16_t id, uint16_t frag, 
        uint8_t ttl, uint8_t prot, uint16_t sum, uint32_t src, uint32_t dst, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_ipv4( 
                        ip_len,         /* length */
                        tos,            /* TOS */
                        id,             /* IP ID */
                        frag,           /* IP Frag */
                        ttl,            /* TTL */
                        prot,           /* protocol */
                        sum,            /* checksum */
                        src,            /* source IP */
                        dst,            /* destination IP */
                        payload,        /* payload */
                        payload_s,      /* payload size */
                        l,              /* libnet handle */
                        ptag);          /* libnet id */
    if (t == -1) {
        err_quit("libnet_build_ipv4 error: %s", libnet_geterror(l));
    }
    return t;
}
