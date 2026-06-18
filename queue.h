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

#endif // QUEUE_H