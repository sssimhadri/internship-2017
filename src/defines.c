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
	node_t *start = NULL;
	char *src, *des; 

     /* lets start with the ether header... */
	eptr = (struct ether_header *) packet;
	src = ether_ntoa((struct ether_addr*)eptr->ether_shost);
	des = ether_ntoa((struct ether_addr*)eptr->ether_dhost);
	push(&start,src);
	push(&start,des);
	printList(start);

//	fprintf(stdout,"ethernet header source: %s",src);
//  fprintf(stdout," destination: %s ", des);
  
    /* check to see if we have an ip packet */
//+++review: use a macro instead of printfs, will allow you to specify different output destinations 
	if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
    {
        myprintf(1,"type: ");
    }else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
    {
        myprintf(2,"type: ");
    }else  if (ntohs (eptr->ether_type) == ETHERTYPE_REVARP)
	{ 
        myprintf(3,"type: ");
    }else {
        myprintf(4,"type: ");
        exit(1);
    }
		
	deleteList(&start);
 
    return eptr->ether_type;
}

void callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
	u_int16_t type = handle_ethernet(args,pkthdr,packet);
	if(type == ETHERTYPE_IP)
	{
		printf("congrats");
	}
	printf("\n");
}
/*
//void begin(dev, netp, maskp, errbuf);
void begin(char *dev, 

pcap_lookupnet(dev,&netp,&maskp,errbuf);

    des = pcap_open_live(dev,BUFSIZ,1,1,errbuf);
    if( des == NULL )
    {
        printf("pcap_open_live: %s \n", errbuf);
        exit(1);
    }
    else
    {
        printf("opened\n");
    }
*/

