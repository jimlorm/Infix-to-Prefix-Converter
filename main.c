#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    QueueNode* current;

    if (q != NULL && q->size > 0) 
    {
        current = q->head;
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

    Queue* infixQueue;
    Queue* prefixQueue;
    ErrorStatus status;
    int finalResult = 0;

    Queue* testInfix;
    Queue* testPrefix;
    ErrorStatus testStatus;
    int testResult = 0;
    int iterations = 10000;

    // INPUT THE EXPRESSION TO BE TESTED FOR EXECUTION TIME
    char* testExpression = "((10 + 20) * (30 + 40)) / 50 + 60 * (70 - 80) + 90 / (10 + 20) * (30 + 40) / 50 + 60 * (70 - 80) + 90 / (10 + 20) * (30 + 40) / 50" ;


    do 
    {

        printf(YELLOW "\n---------------------------------------------\n");
        printf("   INFIX TO PREFIX CONVERTER AND EVALUATOR    \n");
        printf("---------------------------------------------\n" RESET);
        
        printf(CYAN "[1] Convert and Evaluate an Expression\n");
        printf("[2] Execution Time Analysis\n" );
        printf("[3] Exit\n" RESET);
        
        printf(YELLOW "---------------------------------------------\n" RESET);
        printf("Enter choice: ");
        
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) 
        {
            choice = atoi(inputBuffer);

            switch (choice) 
            {
                case 1:
                {
                    infixQueue = createQueue();
                    prefixQueue = createQueue();
                    status = SUCCESS;

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
                    printf(YELLOW "\n------- EXECUTION TIME ANALYSIS -------\n" RESET);

                    clock_t startTime = clock();

                    for (int i = 0; i < iterations; i++) 
                    {
                        testInfix = createQueue();
                        testPrefix = createQueue();
                        testStatus = SUCCESS;

                        tokenize(testExpression, testInfix, &testStatus);
                        
                        if (testStatus == SUCCESS) 
                            hasMismatchedParenthesis(testInfix, &testStatus);
                        if (testStatus == SUCCESS) 
                            isMalformedExpression(testInfix, &testStatus);
                        if (testStatus == SUCCESS) 
                            infixToPrefix(testInfix, testPrefix);
                        if (testStatus == SUCCESS) 
                            testResult = evaluatePrefix(testPrefix, &testStatus);

                        deleteQueue(&testInfix);
                        deleteQueue(&testPrefix);
                    }

                    clock_t endTime = clock();

                    double timeElapsed = ((double)(endTime - startTime) / CLOCKS_PER_SEC) / iterations * 1000;

                    if (testStatus == SUCCESS) 
                    {
                        printf(GREEN "[SUCCESS] Expression was evaluated successfully!\n" RESET);
                        printf("Calculated Answer: %d\n", testResult);
                    }
                    else 
                    {
                        printf(RED "Test failed with error code: %d\n" RESET, testStatus);
                    }

                    printf(YELLOW "Time Elapsed: %lf milliseconds\n" RESET, timeElapsed);
                    break;
                case 3:
                    printf(CYAN "\nExiting program. Goodbye!\n" RESET);
                    break;
                default:
                    printf(RED "\nInvalid choice. Please enter 1, 2, or 3.\n" RESET);
                    break;
            }
        }
    } 
    while (choice != 3); 
    
    return 0; 
}