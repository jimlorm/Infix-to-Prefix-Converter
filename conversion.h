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

int precedenceLevel(Token operator)
{
    int precedence = 0;
    char op = operator.data.symbol;

    if (op == '+' || op == '-')
        precedence = 1;
    else if (op == '*' || op == '/' || op == '%')
        precedence = 2;
    else if (op == '^')
        precedence = 3;

    return precedence;
}

void infixToPrefix(Queue* infixQueue, Queue* prefixQueue)
{
    Stack* operatorStack = createStack();
    Token t;
    bool done;

    reverseQueue(infixQueue);

    while (!isEmptyQueue(infixQueue))
    {
        t = dequeue(infixQueue);

        if (t.type == OPERAND)
            enqueue(prefixQueue, t);
        else if (t.type == PARENTHESIS)
        {
            if (t.data.symbol == '(')
                push(operatorStack, t);
            else 
            {
                while (!isEmptyStack(operatorStack) && top(operatorStack).type != PARENTHESIS)
                    enqueue(prefixQueue, pop(operatorStack));
                
                if (!isEmptyStack(operatorStack)) 
                    pop(operatorStack);
            }
        }
        else if (t.type == OPERATOR)
        {
            done = false;

            while (!isEmptyStack(operatorStack) && top(operatorStack).type == OPERATOR && !done)
            {
                if (t.data.symbol != '^')
                {
                    if (precedenceLevel(top(operatorStack)) > precedenceLevel(t))
                        enqueue(prefixQueue, pop(operatorStack));
                    else
                        done = true;
                }
                else 
                {
                    if (precedenceLevel(top(operatorStack)) >= precedenceLevel(t))
                        enqueue(prefixQueue, pop(operatorStack));
                    else
                        done = true;
                }
            }

            push(operatorStack, t);
        }
    }

    while (!isEmptyStack(operatorStack))
        enqueue(prefixQueue, pop(operatorStack));

    reverseQueue(prefixQueue);

    deleteStack(&operatorStack);
}

#endif // CONVERTER_H