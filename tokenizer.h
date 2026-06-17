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