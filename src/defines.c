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
#include <string.h>

#include "defines.h"
#include "list.h"
#include "queue.h"

#define myprintf(x,...) do { \
						if( x == 1 ) { \
							printf(__VA_ARGS__); \
							fprintf(stdout,"(IP)");\
						} else if( x == 2 ) { \
							printf(__VA_ARGS__); \
							fprintf(stdout,"(ARP)");\
						} else if( x == 3 ) { \
							printf(__VA_ARGS__); \
							fprintf(stdout,"(RARP)");\
						} else { \
							printf(__VA_ARGS__); \
							fprintf(stdout,"(?)"); \
							exit(1); \
						} \
						} while (0)

u_int16_t handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    struct ether_header *eptr;  /* net/ethernet.h */
	node_t *start = NULL; /* create the first node of list.h */
	char *src, *des; 

    /* get the ethernet header */
	eptr = (struct ether_header *) packet;
	/* get the source and destination MAC address */
	src = ether_ntoa((struct ether_addr*)eptr->ether_shost);
	des = ether_ntoa((struct ether_addr*)eptr->ether_dhost);
	/* MAC addresses to the beginning of the list */
	push(&start,src);
	push(&start,des);
	/* print the list */
	printList(start);

	/* delete the list once we are done printing */	
	deleteList(&start);
 
    return eptr->ether_type;
}

void callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
	u_int16_t type = handle_ethernet(args,pkthdr,packet);

	/* print out what type of packet we have received */
	if ( ntohs(type) == ETHERTYPE_IP) {
        myprintf(1,"type: ");
    } else  if ( ntohs(type) == ETHERTYPE_ARP) {
        myprintf(2,"type: ");
    } else  if ( ntohs(type) == ETHERTYPE_REVARP) { 
        myprintf(3,"type: ");
    } else {
        myprintf(4,"type: ");
        exit(1);
    }	

	printf("\n");
}

pcap_t* begin(char *dev, bpf_u_int32 netp, bpf_u_int32 maskp, char errbuf[], struct bpf_program fp, char **argv)
{
	pcap_t* temp;
	pcap_lookupnet(dev,&netp,&maskp,errbuf);

    temp = pcap_open_live(dev,BUFSIZ,1,1,errbuf);
    if( temp == NULL ) {
        printf("pcap_open_live: %s \n", errbuf);
        exit(1);
	} else {
        printf("opened\n");
    }
	
	int comp = pcap_compile( temp, &fp, argv[1], 0, netp );
	
	if(comp == -1) {
		fprintf(stderr,"cant pcap_compile\n");
		exit(1);
	} else {
		fprintf(stdout,"compiled\n");
	}

	int filt = pcap_setfilter(temp,&fp);
    if(filt == -1) {   
        fprintf(stderr,"cant filter\n");
        exit(1);
    } else {   
        fprintf(stdout, "filtered\n");
    }

	return temp;
}

