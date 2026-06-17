#ifndef STACKS_H
#define STACKS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

typedef struct StackNodeTag 
{
    Token token; 
    struct StackNodeTag* next; 
} StackNode;                   

typedef struct StackTag
{
    StackNode* top;            
    int size;
} Stack;

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("\nFailed to create stack");
    }
    else
    {
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

void push(Stack* stack, Token t) 
{
    if (stack == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        StackNode* node = (StackNode*)malloc(sizeof(StackNode)); 
        if (node == NULL)
        {
            printf("\nStack Overflow");
        }
        else
        {
            node->token = t;
            node->next = stack->top;
            stack->top = node;
            stack->size++;
        }
    }
}

Token pop(Stack* stack) 
{
    Token resultToken;
    resultToken.type = ERROR_TOKEN;

    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack Underflow");
    }
    else
    {
        StackNode* temp = stack->top; 
        resultToken = temp->token;

        stack->top = stack->top->next;
        stack->size--;
        
        free(temp);
    }
    return resultToken;
}

Token top(Stack* stack) 
{
    Token resultToken;
    resultToken.type = ERROR_TOKEN;

    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        resultToken = stack->top->token;
    }
    return resultToken;
}

bool isEmptyStack(Stack* stack)
{
    bool result = false;
    if (stack == NULL || stack->size == 0)
    {
        result = true;
    }
    return result;
}

bool isFullStack(Stack* stack)
{
    bool result = false;
    StackNode* testNode = (StackNode*)malloc(sizeof(StackNode)); 
    if (stack == NULL || testNode == NULL)
    {
        result = true;
    }
    else
    {
        free(testNode);
    }
    return result;
}

void deleteStack(Stack** stack)
{
    if (stack == NULL || *stack == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        Stack* temp = *stack;
        StackNode* current = temp->top; 
        StackNode* next = NULL;         

        while(current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        free(temp);
        *stack = NULL;
    }
}

#endif // STACKS_H