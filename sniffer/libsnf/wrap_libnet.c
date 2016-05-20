#include "wrap_libnet.h"

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

struct libnet_ether_addr *Libnet_get_hwaddr(libnet_t *l)
{
    struct libnet_ether_addr *addr = libnet_get_hwaddr(l);
    if (addr == NULL) {
        err_quit("libnet_get_hwaddr error: %s", libnet_geterror(l));
    }
    return addr;
}

uint32_t Libnet_get_ipaddr4(libnet_t *l)
{
    uint32_t addr = libnet_get_ipaddr4(l);
    if (addr == (uint32_t) -1) {
        err_quit("libnet_get_ipaddr4 error: %s", libnet_geterror(l));
    }
    return addr;
}

uint32_t Libnet_name2addr4(libnet_t *l, char *host_name, uint8_t use_name)
{
    uint32_t addr = libnet_name2addr4(l, host_name, use_name);
    if (addr == (uint32_t) -1) {
        err_quit("libnet_name2addr error for %s: %s", host_name, libnet_geterror(l));
    }
    return addr;
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

libnet_ptag_t Libnet_autobuild_ethernet(const uint8_t *dst, uint16_t type, libnet_t *l)
{
    libnet_ptag_t t = libnet_autobuild_ethernet(
                        dst,        /* ethernet destination */
                        type,       /* protocol type */
                        l);         /* libnet handle */
    if (t == -1) {
        err_quit("libnet_autobuild_ethernet error: %s", libnet_geterror(l));
    }
    return t;
}

libnet_ptag_t Libnet_build_arp(uint16_t hrd, uint16_t pro, uint8_t hln, uint8_t pln,
        uint16_t op, const uint8_t *sha, const uint8_t *spa, const uint8_t *tha, const uint8_t *tpa,
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_arp(
                        hrd,        /* hardware addr */
                        pro,        /* protocol addr */
                        hln,        /* hardware addr size */
                        pln,        /* protocol addr size */
                        op,         /* operation type */
                        sha,        /* sender hardware addr */
                        spa,        /* sender protocol addr */
                        tha,        /* target hardware addr */
                        tpa,        /* target protocol addr */
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

libnet_ptag_t Libnet_build_ipv4_options(const uint8_t *options, uint32_t options_s, libnet_t *l,
        libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_ipv4_options(
                        options,        /* options bytes */
                        options_s,      /* options bytes size */
                        l,              /* libnet handle */
                        ptag);          /* libnet id */
    if (t == -1) {
        err_quit("libnet_build_ipv4_options error: %s", libnet_geterror(l));
    }
    return t;
}

libnet_ptag_t Libnet_build_tcp(uint16_t sp, uint16_t dp, uint32_t seq, uint32_t ack,
        uint8_t control, uint16_t win, uint16_t sum, uint16_t urg, uint16_t len, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_tcp(
                        sp,             /* source port */
                        dp,             /* desination port */
                        seq,            /* sequence number */
                        ack,            /* acknowledgement num */
                        control,        /* control flags */
                        win,            /* window size */
                        sum,            /* checksum */
                        urg,            /* urgent pointer */
                        len,            /* TCP packet size */
                        payload,        /* payload */
                        payload_s,      /* payload size */
                        l,              /* libnet handle */
                        ptag);          /* libnet id */
    if (t == -1) {
        err_quit("libnet_build_tcp error: %s", libnet_geterror(l));
    }
    return t;
}

libnet_ptag_t Libnet_build_tcp_options(const uint8_t *options, uint32_t options_s, libnet_t *l,
        libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_tcp_options(
                        options,        /* options bytes */
                        options_s,      /* options bytes size */
                        l,              /* libnet handle */
                        ptag);          /* libnet id */
    if (t == -1) {
        err_quit("libnet_build_tcp_options error: %s", libnet_geterror(l));
    }
    return t;
}

libnet_ptag_t Libnet_build_udp(uint16_t sp, uint16_t dp, uint16_t len, uint16_t sum, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_udp(
                        sp,             /* source port */
                        dp,             /* desination port */
                        len,            /* UDP packet size */
                        sum,            /* checksum */
                        payload,        /* payload */
                        payload_s,      /* payload size */
                        l,              /* libnet handle */
                        ptag);          /* libnet id */
    if (t == -1) {
        err_quit("libnet_build_udp error: %s", libnet_geterror(l));
    }
    return t;
}

libnet_ptag_t Libnet_build_dnsv4(uint16_t h_len, uint16_t id, uint16_t flags,
        uint16_t num_q, uint16_t num_anws_rr, uint16_t num_auth_rr,
        uint16_t num_addi_rr, const uint8_t* payload, uint32_t payload_s, libnet_t *l,
        libnet_ptag_t ptag)
{
    libnet_ptag_t t = libnet_build_dnsv4(
                        h_len,
                        id,
                        flags,
                        num_q,
                        num_anws_rr,    
                        num_auth_rr,
                        num_addi_rr,
                        payload,
                        payload_s,
                        l,
                        ptag);
    if (t == -1) {
        err_quit("libnet_build_dnsv4 error: %s", libnet_geterror(l));
    }
    return t;
}

void Libnet_adv_cull_packet(libnet_t *l, uint8_t **packet, uint32_t *packet_s)
{
    if (libnet_adv_cull_packet(l, packet, packet_s) == -1) {
        err_quit("libnet_adv_cull_packet error: %s", libnet_geterror(l));
    }
}

int Libnet_write(libnet_t *l)
{
    int c = libnet_write(l);
    if (c == -1) {
        err_quit("libnet_write error: %s", libnet_geterror(l));
    }
    return c;
}


