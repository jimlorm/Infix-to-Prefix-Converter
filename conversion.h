#ifndef CONVERTER_H
#define CONVERTER_H

#include "stacks.h"
#include "queue.h"

void reverseQueue(Queue* q)
{
    Token t;
    Stack* tempStack = createStack();

    while (!isEmptyQueue(q))
    {
        t = dequeue(q);
        push(tempStack, t);
    }

    while (!isEmptyStack(tempStack))
    {
        t = pop(tempStack);

        if (t.type == PARENTHESIS)
            t.data.symbol = (t.data.symbol == '(') ? ')' : '(';

        enqueue(q, t);
    }

    deleteStack(&tempStack);
}

int precedenceLevel(char operator)
{

}

void infixToPrefix(Queue* infixQueue, Queue* prefixQueue, ErrorStatus* status)
{
}

#endif // CONVERTER_H