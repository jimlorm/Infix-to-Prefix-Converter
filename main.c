#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// --- LINKING YOUR SEPARATE HEADER FILES ---
#include "queue.h"
#include "stacks.h"

// --- FUNCTION PROTOTYPES ---
int mainMenu(bool *hasFormat, bool *hasExpression, int *current_format, char *expression);
const char* get_format_string(int format);
void wait_for_user();

int main()
{
    int runProgram = 1;
    
    // Local state variables (No global variables used)
    bool hasFormat = false;         
    bool hasExpression = false;     
    int current_format = 0;    
    char expression[256] = "[None Entered]"; 

    while (runProgram == 1)
    {   
        system("cls");
        runProgram = mainMenu(&hasFormat, &hasExpression, &current_format, expression);
    }

    return 0;
}

// --- CORE MENU INTERFACE ---
int mainMenu(bool *hasFormat, bool *hasExpression, int *current_format, char *expression)
{
    int choice;
    int keepRunningResult = 1; 

    // 1. DISPLAY HEADER & CURRENT STATE
    printf("==================================================\n");
    printf("      ARITHMETIC EXPRESSION PROCESSOR (CLI)       \n");
    printf("==================================================\n");
    printf(" [CURRENT STATE]\n");
    printf("  Notation Format : %s\n", get_format_string(*current_format));
    printf("  Expression      : %s\n", expression);
    printf("--------------------------------------------------\n");

    // 2. DYNAMICALLY DISPLAY AVAILABLE OPTIONS
    if (*hasFormat == false)
    {
        printf("  1. Select Notation Format\n");
    }
    else
    {
        printf("  1. Change Notation Format\n");
        if (*hasExpression == false)
        {
            printf("  2. Input Expression\n");
        }
        else
        {
            printf("  2. Edit/Input New Expression\n");
        }
    }
    
    if (*hasFormat == true && *hasExpression == true)
    {
        printf("  3. Convert Expression\n");
        printf("  4. Evaluate (Compute) Expression\n");
    }
    
    if (*hasFormat == true)
    {
        printf("  5. Reset Session\n");
    }
    printf("  0. Exit Program\n");
    printf("--------------------------------------------------\n");
    printf("Enter your choice: ");

    // 3. SAFE INPUT PROCESSING 
    if (scanf("%d", &choice) != 1)
    {
        printf("\n[!] Invalid input! Please enter a number.\n");
        while (getchar() != '\n'); 
        wait_for_user();
    } 
    else if (choice == 0)
    {
        printf("\nExiting program. Goodbye!\n");
        keepRunningResult = 0; 
    } 
    else
    {
        // 4. ACTION ROUTING
        switch (choice)
        {
            case 1:
                system("cls");
                printf("--- Select Notation Format ---\n");
                printf("1. Infix\n");
                printf("2. Postfix\n");
                printf("3. Prefix\n\n");
                printf("Enter choice (1-3): ");
                
                int fmt_choice;
                if (scanf("%d", &fmt_choice) == 1 && fmt_choice >= 1 && fmt_choice <= 3)
                {
                    *current_format = fmt_choice;             
                    *hasFormat = true;                   
                    *hasExpression = false;               
                    strcpy(expression, "[None Entered]"); 
                    printf("\nFormat successfully set!\n");
                }
                else
                {
                    printf("\n[!] Invalid choice. Format not changed.\n");
                    while (getchar() != '\n'); 
                }
                wait_for_user();
                break;

            case 2:
                if (*hasFormat == true)
                {
                    system("cls");
                    printf("--- Enter %s Expression ---\n", get_format_string(*current_format));
                    printf("Enter your expression:\n> ");
                    
                    char temp_expr[256];
                    scanf(" %[^\n]", temp_expr); 

                    // --- GENERAL ERROR VALIDATION ---
                    bool isValid = true;
                    
                    /* @GENERAL TASK:
                       - Check for invalid characters here.
                       - Set isValid = false if anything non-arithmetic/non-alphanumeric is found.
                    */

                    // --- FORMAT-SPECIFIC ERROR VALIDATION ---
                    if (isValid == true)
                    {
                        if (*current_format == 1)
                        {
                            // --- INFIX VALIDATION ---
                            /* @TASK: Insert your validation code here.
                               - Check for parenthesis mismatch
                               - Check for malformed expressions
                               - Check for division by zero
                               If any error triggers, set isValid = false;
                            */
                        } 
                        else if (*current_format == 2)
                        {
                            // --- POSTFIX VALIDATION ---
                            /* @TASK: Insert your validation code here.
                               - Check for malformed expressions
                               - Check for division by zero
                               If any error triggers, set isValid = false;
                            */
                        } 
                        else if (*current_format == 3)
                        {
                            // --- PREFIX VALIDATION ---
                            /* @TASK: Insert your validation code here.
                               - Check for malformed expressions
                               - Check for division by zero
                               If any error triggers, set isValid = false;
                            */
                        }
                    }

                    // --- STATE UPDATE MANAGEMENT & QUEUE LOADING ---
                    if (isValid == true)
                    {
                        strcpy(expression, temp_expr);
                        *hasExpression = true; 
                        
                        // --- INTEGRATION POINT: TOKENIZATION QUEUE ---
                        Queue* tokenQueue = createQueue();
                        int i = 0;
                        while (expression[i] != '\0')
                        {
                            if (expression[i] != ' ')
                            {
                                enqueue(tokenQueue, expression[i]); 
                            }
                            i++;
                        }
                        
                        printf("\nExpression loaded and staged into separate Queue library successfully!\n");
                        
                        // Clean up the memory allocated via your external library functions
                        deleteQueue(&tokenQueue); 
                    }
                    else
                    {
                        printf("\n[!] Expression rejected due to parsing errors.\n");
                    }
                    wait_for_user();
                }
                else
                {
                    printf("\n[!] Option unavailable yet.\n");
                    wait_for_user();
                }
                break;

            case 3:
                if (*hasFormat == true && *hasExpression == true)
                {
                    system("cls");
                    printf("--- Conversion Routing ---\n");
                    printf("Original (%s): %s\n\n", get_format_string(*current_format), expression);
                    
                    if (*current_format == 1)
                    {
                        printf("1. Convert Infix to Prefix\n");
                        printf("2. Convert Infix to Postfix\n\n");
                        printf("Enter choice (1-2): ");
                        int conv_choice;
                        scanf("%d", &conv_choice);
                        
                        /* @TASK: Call conversion modules here
                           - If conv_choice == 1 -> Run Infix to Prefix
                           - If conv_choice == 2 -> Run Infix to Postfix
                        */
                    } 
                    else if (*current_format == 2)
                    {
                        printf("1. Convert Postfix to Infix\n");
                        printf("2. Convert Postfix to Prefix\n\n");
                        printf("Enter choice (1-2): ");
                        int conv_choice;
                        scanf("%d", &conv_choice);
                        
                        if (conv_choice == 1)
                        {
                            /* @TASK: Call Postfix to Infix here */
                        }
                        else if (conv_choice == 2)
                        {
                            /* @TASK: Call Postfix to Prefix here (Call Postfix->Infix, then Infix->Prefix) */
                        }
                    } 
                    else if (*current_format == 3)
                    {
                        printf("1. Convert Prefix to Infix\n");
                        printf("2. Convert Prefix to Postfix\n\n");
                        printf("Enter choice (1-2): ");
                        int conv_choice;
                        scanf("%d", &conv_choice);
                        
                        if (conv_choice == 1)
                        {
                            /* @TASK: Call Prefix to Infix here */
                        }
                        else if (conv_choice == 2)
                        {
                            /* @TASK: Call Prefix to Postfix here (Call Prefix->Infix, then Infix->Postfix) */
                        }
                    }
                    wait_for_user();
                }
                else
                {
                    printf("\n[!] Option unavailable yet.\n");
                    wait_for_user();
                }
                break;

            case 4:
                if (*hasFormat == true && *hasExpression == true)
                {
                    system("cls");
                    printf("--- Evaluation Processing ---\n");
                    printf("Evaluating format [%s]: %s\n\n", get_format_string(*current_format), expression);
                    
                    // --- INTEGRATION POINT: LINKED STACK FROM STACKS.H ---
                    Stack* evalStack = createStack();
                    
                    /* @CONVERT AND COMPUTE / PRINT TASK:
                       - Run stack evaluation algorithms from stacks.h here.
                    */
                    
                    deleteStack(&evalStack);
                    wait_for_user();
                }
                else
                {
                    printf("\n[!] Option unavailable yet.\n");
                    wait_for_user();
                }
                break;

            case 5:
                if (*hasFormat == true)
                {
                    *hasFormat = false;
                    *hasExpression = false;
                    *current_format = 0;
                    strcpy(expression, "[None Entered]");
                    printf("\nSession reset successfully.\n");
                    wait_for_user();
                }
                else
                {
                    printf("\n[!] Option unavailable yet.\n");
                    wait_for_user();
                }
                break;

            default:
                printf("\n[!] Choice out of bounds for the current state.\n");
                wait_for_user();
                break;
        }
    }

    return keepRunningResult; 
}

const char* get_format_string(int format)
{
    const char* resultStr = "[None Selected]";

    if (format == 1)
    {
        resultStr = "INFIX";
    }
    else if (format == 2)
    {
        resultStr = "POSTFIX";
    }
    else if (format == 3)
    {
        resultStr = "PREFIX";
    }

    return resultStr;
}

void wait_for_user()
{
    printf("\nPress Enter to continue...");
    getchar(); 
    getchar(); 
}