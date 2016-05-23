/*pcap_4.c*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> 

#include "wrap_pcap.h"

/* just print a count every time we have a packet...                        */
void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,const u_char*
        packet)
{
    static int count = 1;
    fprintf(stdout,"%d, ",count);
    fflush(stdout);
    count++;
}

int main(int argc,char **argv)
{ 
    char *dev; 
    pcap_t* descr;
    struct bpf_program fp;      /* hold compiled program     */
    bpf_u_int32 maskp;          /* subnet mask               */
    bpf_u_int32 netp;           /* ip                        */

    if(argc != 2) {
        fprintf(stdout,"Usage: %s \"filter program\"\n" ,argv[0]);
        return 0;
    }

    /* grab a device to peak into... */
    dev = Pcap_lookupdev();

    /* ask pcap for the network address and mask of the device */
    Pcap_lookupnet(dev, &netp, &maskp);

    /* open device for reading this time lets set it in promiscuous
     * mode so we can monitor traffic to another machine             */
    descr = Pcap_open_live(dev, BUFSIZ, 1, -1);

    /* Lets try and compile the program.. non-optimized */
    Pcap_compile(descr,&fp,argv[1],0,netp);

    /* set the compiled program as the filter */
    Pcap_setfilter(descr,&fp);

    /** free filter */
    pcap_freecode(&fp);

    /* ... and loop */ 
    pcap_loop(descr,-1,my_callback,NULL);

    return 0;
}

