#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"
#include "conversion.h"
#include "evaluation.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"

void printTokenQueue(Queue* q) 
{
    if (q != NULL && q->size > 0) 
    {
        QueueNode* current = q->head;
        while (current != NULL) 
        {
            if (current->token.type == OPERAND) 
                printf("%d ", current->token.data.value);
            else 
                printf("%c ", current->token.data.symbol);
            
            current = current->next;
        }
        printf("\n");
    }
}

int main() 
{
    char inputBuffer[1000]; 
    int choice = 0;

    do 
    {

        printf(YELLOW "\n---------------------------------------------\n");
        printf("   INFIX TO PREFIX CONVERTER AND EVALUATOR    \n");
        printf("---------------------------------------------\n" RESET);
        
        printf(CYAN "[1] Evaluate a Manual Expression\n");
        printf("[2] Exit\n" RESET);
        
        printf(YELLOW "---------------------------------------------\n" RESET);
        printf("Enter choice: ");
        
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) 
        {
            choice = atoi(inputBuffer);

            switch (choice) 
            {
                case 1:
                {
                    Queue* infixQueue = createQueue();
                    Queue* prefixQueue = createQueue();
                    ErrorStatus status = SUCCESS;
                    int finalResult = 0;

                    printf(CYAN "\nEnter a mathematical expression:\n> " RESET);
                    
                    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) 
                    {
                        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

                        // Tokenization
                        tokenize(inputBuffer, infixQueue, &status);

                        // Validation 1
                        if (status == SUCCESS) 
                            hasMismatchedParenthesis(infixQueue, &status);

                        // Validation 2
                        if (status == SUCCESS) 
                            isMalformedExpression(infixQueue, &status);

                        // Conversion
                        if (status == SUCCESS) 
                        {
                            infixToPrefix(infixQueue, prefixQueue);
                            printf(GREEN "\n[SUCCESS] Converted to Prefix:\n-> " RESET);
                            printTokenQueue(prefixQueue);
                        }

                        // Evaluation
                        if (status == SUCCESS) 
                            finalResult = evaluatePrefix(prefixQueue, &status);

                        // Final Reporting
                        printf(GREEN "\n---------------------------------------------\n" RESET);
                        if (status == SUCCESS) 
                        {
                            printf(GREEN "FINAL ANSWER: %d\n" RESET, finalResult);
                        } 
                        else 
                        {
                            printf(RED "ERROR DETECTED: ");
                            switch(status) 
                            {
                                case ERR_INVALID_CHAR: printf("Invalid character found.\n" RESET); break;
                                case ERR_MISMATCH_PAREN: printf("Mismatched parentheses.\n" RESET); break;
                                case ERR_MALFORMED: printf("Malformed expression.\n" RESET); break;
                                case ERR_DIV_BY_ZERO: printf("Division by zero.\n" RESET); break;
                                default: printf("Unknown error.\n" RESET); break;
                            }
                        }
                        printf(GREEN "---------------------------------------------\n" RESET);
                    }

                    deleteQueue(&infixQueue);
                    deleteQueue(&prefixQueue);
                    break;
                }
                case 2:
                    printf(CYAN "\nExiting program. Goodbye!\n" RESET);
                    break;
                default:
                    printf(RED "\nInvalid choice. Please enter 1 or 2.\n" RESET);
                    break;
            }
        }
    } while (choice != 2); 

    return 0; 
}