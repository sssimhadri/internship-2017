#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0

//structure to represent queue
struct QNode
{
    char* key;
    struct QNode *next;
};

struct Queue
{
        struct QNode *front, *rear;
};

struct QNode* newNode(char* k)
{
        struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}

// function to create a queue of given capacity. 
// It initializes size of queue as 0
struct Queue* createQueue()
{
        struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// function to add k to queue
void enqueue(struct Queue* q, char* k)
{
        // Create a new LL node
    struct QNode *temp = newNode(k);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

int isEmpty(struct Queue *q)
{
        if(q->front == NULL)
        {
                return true;
        }
        else
        {
                return false;
        }
}

// Function to remove a key from given queue q
struct QNode *dequeue(struct Queue *q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
       return NULL;

    // Store previous front and move front one node ahead
    struct QNode *temp = q->front;
    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
       q->rear = NULL;
    return temp;
}
