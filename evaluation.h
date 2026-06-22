#ifndef EVALUATION_H
#define EVALUATION_H

#include "conversion.h"

/*
    Purpose: exponentiation function for integers
    Returns: the result of the exponentiation
    @param : base is the base integer
    @param : exp is the exponent integer
    Pre-condition: exp is a non-negative integer
*/
int power(int base, int exp)
{
    if (exp == 0)
        return 1;
    else 
        return base * power(base, exp - 1);
}

/*
    Purpose: evaluates a prefix expression
    Returns: the result of the evaluation
    @param : prefix is the queue containing the prefix expression
    @param : status is the error status during evaluation
             (it can either the value SUCCESS or ERR_DIV_BY_ZERO or ERR_MALFORMED)
*/

int evaluatePrefix(Queue* prefix, ErrorStatus* status)
{
    Stack* evalStack = createStack();   // will contain the operands to be evaluated 
    Token t;
    int num1, num2;                     // will contain the operand1 and operand2 to be evaluated 
    Token result;                       // will contain the result of the evaluation of num1 and num2
    *status = SUCCESS;
    int finalAnswer = 0;

    result.type = OPERAND;

    // prefix expression must be read from right to left for evaluation
    reverseQueue(prefix);

    while (!isEmptyQueue(prefix) && *status == SUCCESS)
    {
        t = dequeue(prefix);

        // if an operand, push it to the stack
        if (t.type == OPERAND)
            push(evalStack, t);
        // if an operator, pop the two numbers from the stack and perform the indicated operator
        else
        {
            if (evalStack->size < 2)    // if there is not enough operand, the prefix is malformed
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
                    // check here for modulo and division by zero
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
        // the number left from the stack will be the result of the given prefix
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