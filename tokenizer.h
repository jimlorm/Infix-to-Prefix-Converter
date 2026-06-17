#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stacks.h"
#include "queue.h"

void tokenize(const char* expression, Queue* tokenQueue, ErrorStatus* status) 
{
    int i = 0;
    char currentChar; // handles the current character to be tokenized
    int numValue; // will hold the operand
    *status = SUCCESS; // assume there is no error

    while (expression[i] != '\0' && *status == SUCCESS) 
    {
        currentChar = expression[i];

        if (isspace(currentChar)) // check if a space
        {
            i++;
        }
        else if (isdigit(currentChar)) // check if a digit
        {
            numValue = 0;
            
            // keep reading as long as the next character is also a digit
            while (isdigit(expression[i])) 
            {
                numValue = (numValue * 10) + (expression[i] - '0');
                i++;
            }
            
            Token t;
            t.type = OPERAND;
            t.data.value = numValue;
            enqueue(tokenQueue, t);
        }
        // check if an operator
        else if (currentChar == '+' || currentChar == '-' || 
                 currentChar == '*' || currentChar == '/' || 
                 currentChar == '%' || currentChar == '^'   ) 
        {
            Token t;
            t.type = OPERATOR;
            t.data.symbol = currentChar;
            enqueue(tokenQueue, t);
            i++;
        } 
        else if (currentChar == '(' || currentChar == ')') // check if a parenthesis
        {
            Token t;
            t.type = PARENTHESIS;
            t.data.symbol = currentChar;
            enqueue(tokenQueue, t);
            i++;
        }
        else // an invalid character
        {
            *status = ERR_INVALID_CHAR;
        }
    }
}

void hasMismatchedParenthesis(Queue* infix, ErrorStatus* status)
{
    *status = SUCCESS;
    Stack* stack = createStack();
    Queue* infixCopy = copyQueue(infix);
    Token t;

    // Added the status check so it stops early if an error is found
    while (!isEmptyQueue(infixCopy) && *status == SUCCESS) 
    {
        t = dequeue(infixCopy);

        if (t.type == PARENTHESIS) 
        {
            if (t.data.symbol == '(') 
            {
                push(stack, t);
            }
            else if (t.data.symbol == ')') 
            {
                if (!isEmptyStack(stack)) 
                {
                    pop(stack);
                }
                else 
                {
                    *status = ERR_MISMATCH_PAREN; 
                }
            }
        }
    }

    if (*status == SUCCESS && !isEmptyStack(stack)) 
        *status = ERR_MISMATCH_PAREN;

    deleteStack(&stack);
    deleteQueue(&infixCopy);
}

void isMalformedExpression(Queue* infix, ErrorStatus* status)
{
    *status = SUCCESS;
    Queue* infixCopy = copyQueue(infix);
    bool expectOperand = true; 

    while (!isEmptyQueue(infixCopy) && *status == SUCCESS) 
    {
        Token t = dequeue(infixCopy);

        if (t.type == OPERAND) 
        {
            expectOperand = false; 
        }
        else if (t.type == OPERATOR) 
        {
            if (expectOperand) 
            {
                *status = ERR_MALFORMED; 
            }
            else 
            {
                expectOperand = true; 
            }
        }
        else if (t.type == PARENTHESIS) 
        {
            if (t.data.symbol == '(') 
            {
                expectOperand = true;
            } 
            else if (t.data.symbol == ')') 
            {
                if (expectOperand) 
                {
                    *status = ERR_MALFORMED;
                }
                expectOperand = false; 
            }
        }
    }

    if (*status == SUCCESS && expectOperand) 
    {
        *status = ERR_MALFORMED;
    }

    deleteQueue(&infixCopy);
}