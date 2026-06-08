#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodeTag 
{
    int data;
    struct NodeTag* next;
} Node;

typedef struct StackTag
{
    Node* top;
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

void push(Stack* stack, int num)
{
    if (stack == NULL)
        printf("\nStack is NULL");
    
    else
    {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            printf("\nStack Overflow");
        else
        {
            node->data = num;
            node->next = stack->top;
            stack->top = node;
            stack->size++;

            printf("\nPushed %d onto the stack. Stack Size: %d", num, stack->size);
        }
    }
}

int pop(Stack* stack)
{
    int resultValue = -9999;
    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack Underflow");
    }
    
    else
    {
        Node* temp = stack->top;
        int num = temp->data;

        stack->top = stack->top->next;
        stack->size--;
        
        free(temp);
        printf("\nPopped %d from the stack. Stack Size: %d", num, stack->size);
    }
    return resultValue;
}

int top(Stack* stack)
{
    int resultValue = -9999;
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
    Node* testNode = (Node*)malloc(sizeof(Node));
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
    Node* current = stack->top;
    int count = 1;
    while (current != NULL)
    {
        printf("\n%d | %d", count++, current->data);
        current = current->next;
    }
}

void deleteStack(Stack** stack)
{
    if (stack == NULL || *stack == NULL)
        printf("\nStack is NULL");
    
    else
    {
        Stack* temp = *stack;

        Node* current = temp->top;
        Node* next = NULL;

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

Stack* deleteElement(Stack* stack, int n)
{
    Stack* tempS1;
    int x1;
    int j;

    tempS1 = createStack();
    for (j = 1; j < n; j++)
    {
        x1 = pop(stack);
        push(tempS1,x1);
    }
    x1 = pop(stack);

    while(!isEmptyStack(tempS1))
    {
        x1 = pop(tempS1);
        push(stack, x1);
    }

    return stack;
}