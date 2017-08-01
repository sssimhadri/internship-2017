/*
 * Author :
 * purpose :
 * copyright notice :
 *
 *
*/

#include <pcap.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>
#include <netinet/ether.h>

u_int16_t handle_ethernet
        (u_char *args,const struct pcap_pkthdr* pkthdr,const u_char*
        packet);

u_int16_t handle_ethernet
        (u_char *args,const struct pcap_pkthdr* pkthdr,const u_char*
        packet)
{
    struct ether_header *eptr;  /* net/ethernet.h */

    /* lets start with the ether header... */
    eptr = (struct ether_header *) packet;

    fprintf(stdout,"ethernet header source: %s"
            ,ether_ntoa((const struct ether_addr *)&eptr->ether_shost));
    fprintf(stdout," destination: %s "
            ,ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));

    /* check to see if we have an ip packet */
    if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
    {
        fprintf(stdout,"(IP)");
    }else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
    {
        fprintf(stdout,"(ARP)");
    }else  if (ntohs (eptr->ether_type) == ETHERTYPE_REVARP)
    {
        fprintf(stdout,"(RARP)");
    }else {
        fprintf(stdout,"(?)");
        exit(1);
    }

    return eptr->ether_type;
}

void callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
	u_int16_t type = handle_ethernet(args,pkthdr,packet);
	if(type == ETHERTYPE_IP)
		printf("1");
	else if(type == ETHERTYPE_ARP)
		printf("2");
	printf("\n");
}

int main (int argc, char **argv)
{
	int i;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* des;
	const u_char *packet;
	struct pcap_pkthdr header;
	struct bpf_program fp;
	bpf_u_int32 maskp;
	bpf_u_int32 netp;

	if(argc != 2) {
		fprintf(stdout, "Usage: %s \"filter program\"\n", argv[0]);    
		return 0;
	}

	dev = "wlan0";

	pcap_lookupnet(dev,&netp,&maskp,errbuf);

	des = pcap_open_live(dev,BUFSIZ,1,1,errbuf);

	if(des == NULL) {
		printf("pcap_open_live(): %s\n",errbuf);
		exit(1);
	}

	int comp = pcap_compile(des,&fp,argv[1],0,netp);

	if(comp == -1) {
		fprintf(stderr, "cant pcap_compile\n");
		exit(1);
	}

	int filter = pcap_setfilter(des,&fp);

	if(filter == -1) {
		fprintf(stderr, "cant filter\n");
		exit(1);
	}

	pcap_loop(des,10,callback,NULL);

}
