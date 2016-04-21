#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
 
#include "snf.h"

int main(int argc, char **argv)
{
    int i;
    char *dev; 
    pcap_t* descr;      /*you can man it*/
    const u_char *packet;
    struct pcap_pkthdr hdr;     /* pcap.h */
    struct ether_header *eptr;  /* net/ethernet.h */
 
    u_char *ptr; /* printing out hardware header info */
 
    /* grab a device to peak into... */
    dev = Pcap_lookupdev();
    printf("DEV: %s\n",dev);
 
    /* open the device for sniffing.
 
       pcap_t *pcap_open_live(char *device,int snaplen, int prmisc,int to_ms,
       char *ebuf)
 
       snaplen - maximum size of packets to capture in bytes
       promisc - set card in promiscuous mode?
       to_ms   - time to wait for packets in miliseconds before read
       times out
       errbuf  - if something happens, place error string here
 
       Note if you change "prmisc" param to anything other than zero, you will
       get all packets your device sees, whether they are intendeed for you or
       not!! Be sure you know the rules of the network you are running on
       before you set your card in promiscuous mode!!     */

    descr = Pcap_open_live(dev,BUFSIZ,1,0);
 
    /*
       grab a packet from descr (yay!)                    
       u_char *pcap_next(pcap_t *p,struct pcap_pkthdr *h) 
       so just pass in the descriptor we got from         
       our call to pcap_open_live and an allocated        
       struct pcap_pkthdr                                 */
 
    packet = Pcap_next(descr,&hdr);
 
    if(packet == NULL)
    {/* dinna work *sob* */
        printf("Didn't grab packet\n");
        exit(1);
    }
 
    /*  struct pcap_pkthdr {
        struct timeval ts;   time stamp 
        bpf_u_int32 caplen;  length of portion present 
        bpf_u_int32;         lebgth this packet (off wire) 
        }
     */
 
    printf("Grabbed packet of length %d\n",hdr.len);
    printf("Recieved at ..... %s\n",ctime((const time_t*)&hdr.ts.tv_sec)); 
    printf("Ethernet address length is %d\n",ETHER_HDR_LEN);
 
    /* lets start with the ether header... */
    eptr = (struct ether_header *) packet;
 
    /* Do a couple of checks to see what packet type we have..*/
    if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
    {
        printf("Ethernet type hex:%x dec:%d is an IP packet\n",
                ntohs(eptr->ether_type),
                ntohs(eptr->ether_type));
    }else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
    {
        printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
                ntohs(eptr->ether_type),
                ntohs(eptr->ether_type));
    }else {
        printf("Ethernet type %x not IP\n", ntohs(eptr->ether_type));
        exit(1);
    }
 
    /* THANK YOU RICHARD STEVENS!!! RIP*/
    ptr = eptr->ether_dhost;
    i = ETHER_ADDR_LEN;
    printf(" Destination Address:  ");
    do{
        printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
    }while(--i>0);
    printf("\n");
 
    ptr = eptr->ether_shost;
    i = ETHER_ADDR_LEN;
    printf(" Source Address:  ");
    do{
        printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
    }while(--i>0);
    printf("\n");
 
    return 0;
}

