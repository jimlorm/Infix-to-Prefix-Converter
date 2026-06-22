#ifndef CONVERTER_H
#define CONVERTER_H

#include "stacks.h"
#include "queue.h"

/*  
    Purpose: reverses the contents of a queue, the parentheses will also be flipped
    @param: q is the queue to be reversed
*/
void reverseQueue(Queue* q)
{
    Token t;
    Stack* tempStack = createStack();

    // push the elements of the queue into a stack
    while (!isEmptyQueue(q))
    {
        t = dequeue(q);
        push(tempStack, t);
    }

    // then enqueue back the elements to the queue (flipping also the parentheses)
    while (!isEmptyStack(tempStack))
    {
        t = pop(tempStack);

        if (t.type == PARENTHESIS)
            t.data.symbol = (t.data.symbol == '(') ? ')' : '(';

        enqueue(q, t);
    }

    deleteStack(&tempStack);
}

/*
    Purpose: gets the precedence level of an operator
    Returns: either 
             (a) 1 if addition or subtraction
             (b) 2 if multiplication/division/modulo
             (c) 3 if expnentiation
    @param : operator is an operator token in which its precedence will be determined
    Pre-condition: operator must be of type OPERATOR
*/
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

/*
    Purpose: converts an infix expression to prefix expression stored in a queue
    @param : infixQueue is where the infix expression is stored
    @param : prefixQueue is where the equivalent prefix expression of the given infix will be stored
    Pre-condition: infixQueue must be validated already using the hasMismatchedParenthesis 
                   and isMalformedExpression with SUCCESS status
*/
void infixToPrefix(Queue* infixQueue, Queue* prefixQueue)
{
    Stack* operatorStack = createStack();
    Token t;
    bool done;      // 

    // reverse first the infix queue
    reverseQueue(infixQueue);

    while (!isEmptyQueue(infixQueue))
    {
        t = dequeue(infixQueue);

        // if an operand, add it to the result
        if (t.type == OPERAND)
            enqueue(prefixQueue, t);
        else if (t.type == PARENTHESIS)
        {
            // if a left parenthesis, add it to the operator stack
            if (t.data.symbol == '(')
                push(operatorStack, t);
            else // if a right parenthesis,
            {
                /* transfer the elements of the operator stack to the result queue until it reaches a 
                    left parenthesis (finding a pair) */
                while (!isEmptyStack(operatorStack) && top(operatorStack).type != PARENTHESIS)
                    enqueue(prefixQueue, pop(operatorStack));
                
                // discard the left parenthesis
                if (!isEmptyStack(operatorStack)) 
                    pop(operatorStack);
            }
        }
        else if (t.type == OPERATOR)
        {
            done = false;

            while (!isEmptyStack(operatorStack) && top(operatorStack).type == OPERATOR && !done)
            {
                /* if left associative, precedence of the next operator must be strictly greater than 
                the precedence of the current operator */
                if (t.data.symbol != '^') 
                {
                    if (precedenceLevel(top(operatorStack)) > precedenceLevel(t))
                        enqueue(prefixQueue, pop(operatorStack));
                    else
                        done = true;
                }
                /* if right associative, precedence of the next operator must be greater than or equal from
                the precedence of the current operator */
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

    // then enqueue the remaining operators in the stack
    while (!isEmptyStack(operatorStack))
        enqueue(prefixQueue, pop(operatorStack));

    // reverse back again to get the prefix result
    reverseQueue(prefixQueue);

    deleteStack(&operatorStack);
}

#endif // CONVERTER_H