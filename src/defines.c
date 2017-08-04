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

//declaring node structure
typedef struct node
{
    char* data;
    struct node *next;
} node_t; 

//adding data to beginning of linked list
void push(node_t **head_ref, char *new_data)
{
    // Allocate memory for node
    node_t *new_node = malloc(sizeof(node_t));
    //check if the memory allocation was successfull
    if (!new_node) 
    {   
        //+++review: add a perror message here
        exit(EXIT_FAILURE);
    }   
        
    //assign data to node  
    new_node->data = new_data;
    //assign head_ref as next node
    new_node->next = *head_ref;
 
    // Change head pointer as new node is added at the beginning
    *head_ref = new_node;
}

//printing data in list
void printList(struct node *node)
{
	if( node == NULL )
	{
		printf("cant print cause empty\n");
	}
    while (node != NULL)
    {   
        printf("%s\n",node->data);
        node = node->next;
    }   
}

void deleteList(struct node **head)
{
	node_t *curr = *head;
	node_t *next;

	while(curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	
	*head = NULL;
}

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
//    fprintf(stdout," destination: %s ", des);
  
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

