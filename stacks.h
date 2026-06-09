#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackNodeTag 
{
    char data; 
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

void push(Stack* stack, char num) 
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
            node->data = num;
            node->next = stack->top;
            stack->top = node;
            stack->size++;
            printf("\nPushed %c onto the stack. Stack Size: %d", num, stack->size);
        }
    }
}

char pop(Stack* stack) 
{
    char resultValue = '\0'; 
    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack Underflow");
    }
    else
    {
        StackNode* temp = stack->top; 
        char num = temp->data; 

        stack->top = stack->top->next;
        stack->size--;
        
        free(temp);
        resultValue = num;
        printf("\nPopped %c from the stack. Stack Size: %d", num, stack->size);
    }
    return resultValue;
}

char top(Stack* stack) 
{
    char resultValue = '\0'; 
    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        resultValue = stack->top->data;
    }
    return resultValue;
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

void printStack(Stack* stack)
{
    StackNode* current = stack->top; 
    int count = 1;
    while (current != NULL)
    {
        printf("\n%d | %c", count++, current->data);
        current = current->next;
    }
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