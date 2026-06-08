#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    }
    else 
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }

    return queue;
}

void enqueue(Queue* queue, int num)
{
    if (queue == NULL)
    {
        printf("\nQueue is NULL");
    }
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
    int resultValue = -9999;
    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue Underflow");
    }
    else
    {
        Node* temp = queue->head;
        resultValue = temp->data;

        queue->head = queue->head->next;
        queue->size--;

        if(queue->size == 0)
        {
            queue->tail = NULL;
        }
        
        free(temp);
        printf("\nDequeued %d from the queue. Queue Size: %d", resultValue, queue->size);
    }
    return resultValue;
}

int Head(Queue* queue)
{
    int resultValue = -9999;
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

int Tail(Queue* queue)
{
    int resultValue = -9999;
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
    Node* testNode = (Node*)malloc(sizeof(Node));
    
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

void printQueue(Queue* queue)
{
    if (queue == NULL)
    {
        printf("\nQueue does not exist.");
    }
    else
    {
        Node* current = queue->head;
        int count = 1;
        while (current != NULL)
        {
            printf("\n%d | %d", count++, current->data);
            current = current->next;
        }
    }
}

