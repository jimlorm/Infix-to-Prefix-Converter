#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stacks.h"
#include "queue.h"

/*
    Purpose: copies the contents of the source queue
    Returns: the destination queue
    @param : src is the source queue where its contents will be copied
*/
Queue* copyQueue(Queue* src) 
{
    Queue* dest = createQueue(); 
    QueueNode* current = src->head;

    if (src == NULL) 
        return NULL;

    // copy until it reach the end
    while (current != NULL) 
    {
        enqueue(dest, current->token); 
        current = current->next; 
    }
    
    return dest;
}

/*
    Purpose: converts a raw string to a queue that accepts tokens
    @param : expression is the string to be tokenized
    @param : tokenQueue is the queue where the tokens of the tokenized string are stored
    @param : status is the error status during the tokenization 
             (it can either have the value SUCCESS or ERR_INVALID_CHAR at the end of the tokenization)
*/
void tokenize(const char* expression, Queue* tokenQueue, ErrorStatus* status) 
{
    int i = 0;
    char currentChar;       // handles the current character to be tokenized
    int numValue;           // will hold the operand
    *status = SUCCESS;      // assume there is no error

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

/*
    Purpose: checks if the infix queue has mismatched parenthesis
    @param : infix is the queue where the infix expression is stored that will be checked
    @param : status is the error status during the checking
             (it can either have the value SUCCESS or ERR_MISMATCH_PAREN at the end of checking)
*/
void hasMismatchedParenthesis(Queue* infix, ErrorStatus* status)
{   
    *status = SUCCESS;   // assume no error
    Stack* tempStack = createStack();   
    Queue* infixCopy = copyQueue(infix);
    Token t;

    while (!isEmptyQueue(infixCopy) && *status == SUCCESS) 
    {
        t = dequeue(infixCopy);

        if (t.type == PARENTHESIS) 
        {
            // push to the stack if left parenthesis
            if (t.data.symbol == '(') 
            {
                push(tempStack, t);
            }
            // pop the left parenthesis from the stack if right parenthesis
            else if (t.data.symbol == ')') 
            {
                if (!isEmptyStack(tempStack)) 
                {
                    pop(tempStack);
                }
                else // has no pair of left parenthesis left in the stack
                {
                    *status = ERR_MISMATCH_PAREN; 
                }
            }
        }
    }

    // if all the right parentheses have pairs but there was some leftover left parenthesis in the stack
    if (*status == SUCCESS && !isEmptyStack(tempStack)) 
        *status = ERR_MISMATCH_PAREN;

    deleteStack(&tempStack);
    deleteQueue(&infixCopy);
}

/*
    Purpose: checks if the infix queue is a malformed expression
    @param : infix is the queue where the infix expression is stored that will be checked
    @param : status is the error status during the checking
             (it can either have the value SUCCESS or ERR_MALFORMED at the end of checking)
*/
void isMalformedExpression(Queue* infix, ErrorStatus* status)
{
    *status = SUCCESS;                  // assume no error
    Queue* infixCopy = copyQueue(infix);
    bool expectOperand = true;          // will be used as an indicator if the next token must be an operand

    while (!isEmptyQueue(infixCopy) && *status == SUCCESS) 
    {
        Token t = dequeue(infixCopy);

        // if the current token is operand, then the next token must not be an operand too
        if (t.type == OPERAND) 
        {
            expectOperand = false; 
        }
        else if (t.type == OPERATOR) 
        {
            // if the current token is an operator but we expected an operand, then it must be malformed
            if (expectOperand) 
            {
                *status = ERR_MALFORMED; 
            }
            // after the operator must be an operand
            else 
            {
                expectOperand = true; 
            }
        }
        else if (t.type == PARENTHESIS) 
        {
            // if the current token is a right parenthesis, then the next token must be an operand
            if (t.data.symbol == '(') 
            {
                expectOperand = true;
            } 
            // else, the next should be an operator or another parenthesis
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

    // if the infix queue is already empty but we still expects an operand at the end, then it must be malformed
    if (*status == SUCCESS && expectOperand) 
    {
        *status = ERR_MALFORMED;
    }

    deleteQueue(&infixCopy);
}

#endif // TOKENIZER_H