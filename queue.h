#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

typedef struct QueueNodeTag 
{
    Token token; 
    struct QueueNodeTag* next; 
} QueueNode;                   

typedef struct QueueTag
{
    QueueNode* head;           
    QueueNode* tail;           
    int size;
} Queue;

/*
    Purpose: initializes a new, empty queue in memory
    Returns: a pointer to the newly created queue
*/
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

/*
    Purpose: inserts a new token at the tail of the queue
    @param : queue is the pointer to the queue where the token will be added
    @param : t is the token to be inserted
*/
void enqueue(Queue* queue, Token t) 
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
            node->token = t;
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
        }
    }
}

/*
    Purpose: removes and returns the token at the head of the queue
    Returns: the token that was removed, or an ERROR_TOKEN if the queue is empty
    @param : queue is the pointer to the queue to dequeue from
*/
Token dequeue(Queue* queue) 
{
    Token resultToken;
    resultToken.type = ERROR_TOKEN;

    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue Underflow");
    }
    else
    {
        QueueNode* temp = queue->head; 
        resultToken = temp->token;

        queue->head = queue->head->next;
        queue->size--;

        if(queue->size == 0)
        {
            queue->tail = NULL;
        }
        
        free(temp);
    }
    return resultToken;
}

/*
    Purpose: retrieves the token at the head of the queue without removing it
    Returns: the token at the head, or an ERROR_TOKEN if the queue is empty
    @param : queue is the pointer to the queue being checked
*/
Token Head(Queue* queue) 
{
    Token resultToken;
    resultToken.type = ERROR_TOKEN;

    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        resultToken = queue->head->token;
    }
    return resultToken;
}

/*
    Purpose: retrieves the token at the tail of the queue without removing it
    Returns: the token at the tail, or an ERROR_TOKEN if the queue is empty
    @param : queue is the pointer to the queue being checked
*/
Token Tail(Queue* queue) 
{
    Token resultToken;
    resultToken.type = ERROR_TOKEN;

    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        resultToken = queue->tail->token; 
    }
    return resultToken;
}

/*
    Purpose: checks if the given queue contains no elements
    Returns: true if the queue is empty or NULL, false otherwise
    @param : queue is the pointer to the queue being checked
*/
bool isEmptyQueue(Queue* queue)
{
    bool emptyStatus = false;
    if (queue == NULL || queue->size == 0)
    {
        emptyStatus = true;
    }
    return emptyStatus; 
}

/*
    Purpose: checks if the system has run out of memory to allocate a new queue node
    Returns: true if memory allocation fails, false if memory is available
    @param : queue is the pointer to the queue being checked
*/
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

/*
    Purpose: frees all memory associated with the queue and its nodes
    @param : queue is a double pointer to the queue so it can be safely set to NULL after deletion
*/
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

#endif // QUEUE_H