#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNodeTag 
{
    char data; 
    struct QueueNodeTag* next; 
} QueueNode;                   

typedef struct QueueTag
{
    QueueNode* head;           
    QueueNode* tail;           
    int size;
} Queue;

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("\nFailed to create queue");
    }
    else 
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

void enqueue(Queue* queue, char num) 
{
    if (queue == NULL)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode)); 
        if (node == NULL)
        {
            printf("\nQueue Overflow");
        }
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
            printf("\nQueued %c onto the queue. Queue Size: %d", num, queue->size);
        }
    }
}

char dequeue(Queue* queue) 
{
    char resultValue = '\0'; 
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue Underflow");
    }
    else
    {
        QueueNode* temp = queue->head; 
        resultValue = temp->data;

        queue->head = queue->head->next;
        queue->size--;

        if(queue->size == 0)
        {
            queue->tail = NULL;
        }
        
        free(temp);
        printf("\nDequeued %c from the queue. Queue Size: %d", resultValue, queue->size);
    }
    return resultValue;
}

char Head(Queue* queue) 
{
    char resultValue = '\0'; 
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        resultValue = queue->head->data;
    }
    return resultValue;
}

char Tail(Queue* queue) 
{
    char resultValue = '\0'; 
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        resultValue = queue->tail->data; 
    }
    return resultValue;
}

bool isEmptyQueue(Queue* queue)
{
    bool emptyStatus = false;
    if (queue == NULL || queue->size == 0)
    {
        emptyStatus = true;
    }
    return emptyStatus; 
}

bool isFullQueue(Queue* queue)
{
    bool fullStatus = false;
    QueueNode* testNode = (QueueNode*)malloc(sizeof(QueueNode)); 
    if (testNode == NULL) 
    {
        fullStatus = true;
    }
    else
    {
        free(testNode);
    }
    return fullStatus;
}

void deleteQueue(Queue** queue)
{
    if (queue == NULL || *queue == NULL)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        Queue* temp = *queue;
        QueueNode* current = temp->head; 
        QueueNode* next = NULL;          

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

void printQueue(Queue* queue)
{
    if (queue == NULL)
    {
        printf("\nQueue does not exist.");
    }
    else
    {
        QueueNode* current = queue->head; 
        int count = 1;
        while (current != NULL)
        {
            printf("\n%d | %c", count++, current->data);
            current = current->next;
        }
    }
}