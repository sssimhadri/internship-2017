#include <defines.h>
#include <list.h>
#include <queue.h>

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
						} \
						} while (0)

u_int16_t handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    struct ether_header *eptr;  /* net/ethernet.h */
	char *src, *des; 
	FILE *fptr;

    /* get the ethernet header */
	eptr = (struct ether_header *) packet;
	/* get the source and destination MAC address */
	src = ether_ntoa((struct ether_addr*)eptr->ether_shost);
	des = ether_ntoa((struct ether_addr*)eptr->ether_dhost);

	/* adds source and destination MAC addresses to .pcap file
	 * prints source and destination MAC addresses
	 */
	fptr = fopen("test.pcap","a");
	fprintf(fptr,"%s\n",src);
	printf("source MAC: %s\n",src);
	fprintf(fptr,"%s\n",des);
	printf("destination MAC: %s\n",des);
	fclose(fptr);
 
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
    }	

	printf("\n");
}

void storing(int num)
{
	node_t *A[num];
	char *line[num];
	int i, k, x, y;
	unsigned long result;
	unsigned long in;
	int index;
	FILE *f = fopen("test.pcap","r");
	
	/* add test.pcap to string array */
	for( i = 0; i < num; i++ ) {
		line[i] = malloc(sizeof(char)*256);
		fscanf(f,"%s",line[i]);
	}

	fclose(f);
	
	/* initialize space for array of linked list */
	for( k = 0; k < num; k++ ) {
		A[k] = NULL;
	}

	/* hash MAC addresses and store them in array of linked list */
	for( x = 0; x < num; x++ ) {
		result = hash(line[x]);
		in = result%num;
		index = (int)in;
		if( A[index] == NULL ) {
			node_t *start = NULL;
			push(&start,line[x]);
			A[index] = start;
		}
		else {
			push(&A[index],line[x]);
		}
	}

	printf("printing from array of linked list...\n");
	for( y = 0; y < num; y++ ) {
		printList(A[y]);
	}
}





















