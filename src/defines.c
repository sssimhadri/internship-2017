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
//	node_t *start = NULL; /* create the first node of list.h */
	char *src, *des; 
	FILE *fptr;

    /* get the ethernet header */
	eptr = (struct ether_header *) packet;
	/* get the source and destination MAC address */
	src = ether_ntoa((struct ether_addr*)eptr->ether_shost);
	des = ether_ntoa((struct ether_addr*)eptr->ether_dhost);

	fptr = fopen("test.pcap","a");
	fprintf(fptr,"source: %s\n",src);
	fprintf(fptr,"des: %s\n",des);
	fclose(fptr);

	/* MAC addresses to the beginning of the list */
//	push(&start,des);
	/* print the list */
//	printList(start);

	/* delete the list once we are done printing */	
//	deleteList(&start);
 
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

void addQueue()
{
	char line[256];
	int i = 0;
	node_t *A[100];
	for( i = 0; i < 100; i++ ) {
		A[i] = NULL;
	}
	struct Queue *q = createQueue();
	FILE *f = fopen("test.pcap","r");
	while( fgets(line, sizeof(line), f) != NULL ) {
		enqueue(q,line);
		printf("%s",line);
	}

	fclose(f);
	
//	int k = 0;
	while( isEmpty(q) == 0 ) {
//		node_t *start = NULL;
		struct QNode *n = dequeue(q);
		char* str = n->key;
		printf("%s",str);
	//	push(&start, str);
	//	printf("k is %d\n",k);
	//	A[k] = start;
	//	k++;
	}

	int j;
	for( j = 0; j < 20; j++ ) {
	//	printList(A[j]);
	}
	
}





















