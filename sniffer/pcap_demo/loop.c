#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>

#include "wrap_pcap.h"

/* callback function that is passed to pcap_loop(..) and called each time 
 * a packet is recieved                                                    */
void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,const u_char*
		packet)
{
	static int count = 1;
	fprintf(stdout,"%d, ",count);
	if(count == 4)
		fprintf(stdout,"Come on baby sayyy you love me!!! ");
	if(count == 7)
		fprintf(stdout,"Tiiimmmeesss!! ");
	fflush(stdout);
	count++;
}

int main(int argc,char **argv)
{ 
	char *dev; 
	pcap_t* descr;

	if(argc != 2){ fprintf(stdout,"Usage: %s numpackets\n",argv[0]);return 0;}

	/* grab a device to peak into... */
	dev = Pcap_lookupdev();

	/* open device for reading */
	descr = Pcap_open_live(dev,BUFSIZ,1,-1);

	/* allright here we call pcap_loop(..) and pass in our callback function */
	/* int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)*/
	pcap_loop(descr,atoi(argv[1]),my_callback,NULL);

	fprintf(stdout,"\nDone processing packets... wheew!\n");
	return 0;
}


