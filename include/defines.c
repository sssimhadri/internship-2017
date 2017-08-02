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

//+++review: move the file to the src directory 
//+++review: compilation error 
typedef struct node {
	void *data;
	struct node *next;
}; 

void push(struct node** head_ref, void *new_data, size_t data_size)
{
    // Allocate memory for node
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    //+++review : check if the memory allocation was successfull
    if (!new_node) {
        //+++review: add a perror message here
        exit(EXIT_FAILURE);
    }
 
    new_node->data = malloc(data_size);
    new_node->next = (*head_ref);
 
    // Copy contents of new_data to newly allocated memory.
    // Assumption: char takes 1 byte.
    //+++review: declare the variable at the top or as int i =0 or if its a block of code then at the top
    int i;
    //+++review: 'for' loops and if condition checks should be within braces 
    for (i=0; i<data_size; i++) 
        *(char *)(new_node->data + i) = *(char *)(new_data + i);
 
    // Change head pointer as new node is added at the beginning
    (*head_ref)    = new_node;
}

void printList(struct node *node, void (*fptr)(void *))
{
    while (node != NULL)
    {
        (*fptr)(node->data);
        node = node->next;
    }
}

//+++review: use a macro instead of printfs, will allow you to specify different output destinations
void printChar(void *c)
{
	printf("printing from list\n");
	printf(" %s", *(char*)c);
}

void store(char *src, char *des) {
	struct node* start = NULL;
	unsigned char_size = sizeof(char*);
	push(&start, &src, char_size);
	printList(start, printChar);
}

u_int16_t handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    struct ether_header *eptr;  /* net/ethernet.h */
	char *src, *des; 

     /* lets start with the ether header... */
    eptr = (struct ether_header *) packet;
	src = ether_ntoa((const struct ether_addr *)&eptr->ether_shost);
	des = ether_ntoa((const struct ether_addr *)&eptr->ether_dhost);

	store(src,des);
 
//     fprintf(stdout,"ethernet header source: %s",src);
//     fprintf(stdout," destination: %s ", des);
  
     /* check to see if we have an ip packet */
//+++review: use a macro instead of printfs, will allow you to specify different output destinations
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
                 printf("why is this not printing");
        else if(type == ETherTYPE_ARP)
                printf("this is an arp packet");
        printf("\n");
}

