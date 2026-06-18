#ifndef EVALUATION_H
#define EVALUATION_H

#include "conversion.h"

int power(int base, int exp)
{
    if (exp == 0)
        return 1;
    else 
        return base * power(base, exp - 1);
}

int evaluatePrefix(Queue* prefix, ErrorStatus* status)
{
    Stack* evalStack = createStack();
    Token t;
    int num1, num2;
    Token result;
    *status = SUCCESS;
    int finalAnswer = 0;

    result.type = OPERAND;

    reverseQueue(prefix);

    while (!isEmptyQueue(prefix) && *status == SUCCESS)
    {
        t = dequeue(prefix);

        if (t.type == OPERAND)
            push(evalStack, t);
        else
        {
            if (evalStack->size < 2)
                *status = ERR_MALFORMED;
            else
            {
                num1 = pop(evalStack).data.value;
                num2 = pop(evalStack).data.value;

                switch(t.data.symbol)
                {
                    case '+': 
                        result.data.value = num1 + num2;
                        push(evalStack, result);
                        break;
                    case '-':
                        result.data.value = num1 - num2;
                        push(evalStack, result);
                        break;
                    case '*':
                        result.data.value = num1 * num2;
                        push(evalStack, result);
                        break;
                    case '/':
                        if (num2 == 0)
                            *status = ERR_DIV_BY_ZERO;
                        else
                        {
                            result.data.value = num1 / num2;
                            push(evalStack, result);
                        }
                        break;
                    case '%':
                        if (num2 == 0)
                            *status = ERR_DIV_BY_ZERO;
                        else
                        {
                            result.data.value = num1 % num2;
                            push(evalStack, result);
                        }
                        break;
                    case '^':
                        result.data.value = power(num1, num2);
                        push(evalStack, result);
                        break;
                }
            }
        }
    }
    
    if (*status == SUCCESS)
    {
        if (evalStack->size == 1)
            finalAnswer = pop(evalStack).data.value;
        else
            *status = ERR_MALFORMED;
    }

    deleteStack(&evalStack);

    if (*status != SUCCESS)
        return -1;
    else
        return finalAnswer;
}

#endif // EVALUATION_H