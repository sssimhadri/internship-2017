#include <stdlib.h>
#include <stdio.h>

/* defining type node */ 
typedef struct node
{
    char* data;
    struct node *next;
} node_t;

/* hash function to store network packets */
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
	{
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash;
}

/* adding data to beginning of linked list */
void push(node_t **head_ref, char *new_data)
{
    /* Allocate memory for node */
    node_t *new_node = malloc(sizeof(node_t));
    /* check if the memory allocation was successfull */
    if (!new_node) {
		exit(EXIT_FAILURE);
    }

    /* assign data to node */
    new_node->data = new_data;
    /* assign head_ref as next node */
    new_node->next = *head_ref;

    /* Change head pointer as new node is added at the beginning */
    *head_ref = new_node;
}

/* printing data in list */
void printList(struct node *node)
{
    if( node == NULL ) {
        printf("cant print cause empty\n");
    }
    while (node != NULL) {
		int i = 0;
		//unsigned long result = hash(node->data);
		switch (i) {
			case 0 : 
        		printf("destination MAC: %s\n",node->data);
        		//printf("hashed MAC: %lu\n",result);
        		node = node->next;
				i++;
			case 1 : 
				printf("source MAC: %s\n",node->data);
            	//printf("hashed MAC: %lu\n",result);
            	node = node->next;
            	i--;
		}
    }
}

/* delete the list */
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

