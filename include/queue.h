#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0

/* struct to represtent queue */ 
struct QNode
{
    char* key;
    struct QNode *next;
};

struct Queue
{
	struct QNode *front, *rear;
};

/* create new node to queue */
struct QNode* newNode(char* k)
{
	struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
   	temp->key = k;
    temp->next = NULL;
    return temp;
}

/*
 * function to create queue
 * size is initialized to 0
 */
struct Queue* createQueue()
{
	struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

/* add k to the queue */
void enqueue(struct Queue* q, char* k)
{
	/* create temp node */
    struct QNode *temp = newNode(k);

	/* if queue is empty, new node is both front and rear */
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }

	/* add new node at end of queue and change rear */
    q->rear->next = temp;
    q->rear = temp;
}

/* check to see if queue is empty */
int isEmpty(struct Queue *q)
{
	if(q->front == NULL) {
		return true;
	} else {
		return false;
	}
}

/* function to remove a key from given queue q */
struct QNode *dequeue(struct Queue *q)
{
    /* if queue is empty, return NULL */
    if (q->front == NULL) {
       return NULL;
	}

    /* store previous front and move front one node ahead */
    struct QNode *temp = q->front;
    q->front = q->front->next;

    /* if front becomes NULL, then change rear also as NULL */
    if (q->front == NULL) {
       q->rear = NULL;
	}

    return temp;
}

