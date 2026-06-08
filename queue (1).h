#include <stdio.h>
#include <stdlib.h>

typedef struct NodeTag 
{
    int data;
    struct NodeTag* next;
} Node;

typedef struct QueueTag
{
    Node* head;
    Node* tail;
    int size;
} Queue;

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("\nFailed to create queue");
        return NULL;
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void deleteQueue(Queue** queue)
{
    if (queue == NULL || *queue == NULL)
        printf("\nQueue is NULL");
    
    else
    {
        Queue* temp = *queue;

        Node* current = temp->head;
        Node* next = NULL;

        while(current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        free(temp);
        *queue = NULL;
    }
}

void enqueue(Queue* queue, int num)
{
    if (queue == NULL)
        printf("\nQueue is NULL");
    
    else
    {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            printf("\nQueue Overflow");
        else
        {
            node->data = num;
            node->next = NULL;

            if(queue->size == 0)
            {
                queue->head = node;
                queue->tail = node;
            }
            else
            {
                queue->tail->next = node;
                queue->tail = node;
            }
            queue->size++;

            printf("\nQueued %d onto the queue. Queue Size: %d", num, queue->size);
        }
    }
}

int dequeue(Queue* queue)
{
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue Underflow");
        return -9999;
    }
    else
    {
        Node* temp = queue->head;
        int num = temp->data;

        queue->head = queue->head->next;
        queue->size--;

        if(queue->size == 0)
            queue->tail = NULL;
        
        free(temp);
        printf("\nDequeued %d from the queue. Queue Size: %d", num, queue->size);
        return num;
    }
}

int queuehead(Queue* queue)
{
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
        return -9999;
    }
    return queue->head->data;
}

int queuetail(Queue* queue)
{
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
        return -9999;
    }
    return queue->tail->data;
}

int isQueueEmpty(Queue* queue)
{
    int num = 0;
    if (queue == NULL || queue->size == 0)
        num = 1;
    return num;
}

void printQueue(Queue* queue)
{
    Node* current = queue->head;
    int count = 1;
    while (current != NULL)
    {
        printf("\n%d | %d", count++, current->data);
        current = current->next;
    }
}

