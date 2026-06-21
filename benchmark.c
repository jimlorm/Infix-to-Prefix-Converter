#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tokenizer.h"
#include "conversion.h"
#include "evaluation.h"

void appendString(char* destination, const char* source, int* currentLength) 
{
    int i = 0;
    while (source[i] != '\0') 
    {
        destination[*currentLength] = source[i];
        (*currentLength)++;
        i++;
    }
    destination[*currentLength] = '\0';
}

//   cat: 1 = standard operator hierarchy rules, 2 = Deep Nesting, 3 = tokenizer string-handling, 4 = Structural violations
void generateTestData(char* buffer, int targetTokens, int cat) 
{
    int currentLength = 0;
    int itemsAdded = 0;
    buffer[0] = '\0';

    if (cat == 1) 
    {
        appendString(buffer, "1", &currentLength);
        itemsAdded = 1;
        while (itemsAdded < targetTokens) 
        {
            if (itemsAdded % 4 == 1)
                appendString(buffer, " + ", &currentLength);
            else if (itemsAdded % 4 == 2)
                appendString(buffer, " * ", &currentLength);
            else
                appendString(buffer, " - ", &currentLength);
            
            appendString(buffer, "1", &currentLength);
            itemsAdded += 2; /* Added an operator and an operand */
        }
    } 
    else if (cat == 2) 
    {
        int parenPairs = (targetTokens - 3) / 2;
        int i = 0;
        
        while (i < parenPairs)
        {
            appendString(buffer, "(", &currentLength);
            i++;
        }
        appendString(buffer, "1 + 1", &currentLength);
        
        i = 0;
        while (i < parenPairs) 
        {
            appendString(buffer, ")", &currentLength);
            i++;
        }
    } 
    else if (cat == 3) 
    {
        appendString(buffer, "123456", &currentLength);
        itemsAdded = 1;
        while (itemsAdded < targetTokens) 
        {
            appendString(buffer, "       +        ", &currentLength);
            appendString(buffer, "654321", &currentLength);
            itemsAdded += 2;
        }
    } 
    else if (cat == 4) 
    {
        appendString(buffer, "1", &currentLength);
        itemsAdded = 1;
        while (itemsAdded < targetTokens - 2) 
        {
            appendString(buffer, " + 1", &currentLength);
            itemsAdded += 2;
        }
        appendString(buffer, " + + ", &currentLength);
    }
}

int main() 
{
    int N;
    int cat;

    char* expressionBuffer = (char*)malloc(50000 * sizeof(char));

    printf("TokenCount\tCategory1(ms)\tCategory2(ms)\tCategory3(ms)\tCategory4(ms)\tTheoreticalBaseline\n");

    for (N = 5; N <= 100; N += 5) 
    {
        double results[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

        cat = 1;
        while (cat <= 4) 
        {
            generateTestData(expressionBuffer, N, cat);
            
            int iterations = 15000;
            int iter = 0;
            
            clock_t startTime = clock();
            while (iter < iterations) 
            {
                Queue* infixQueue = createQueue();
                Queue* prefixQueue = createQueue();
                ErrorStatus status = SUCCESS;
                int tempAns = 0;

                tokenize(expressionBuffer, infixQueue, &status);
                
                if (status == SUCCESS)
                    hasMismatchedParenthesis(infixQueue, &status);
                if (status == SUCCESS)
                    isMalformedExpression(infixQueue, &status);
                if (status == SUCCESS)
                    infixToPrefix(infixQueue, prefixQueue);
                if (status == SUCCESS)
                    tempAns = evaluatePrefix(prefixQueue, &status);

                (void)tempAns; 

                deleteQueue(&infixQueue);
                deleteQueue(&prefixQueue);
                iter++;
            }
            clock_t endTime = clock();

            double timeElapsed = ((double)(endTime - startTime) / CLOCKS_PER_SEC) / iterations * 1000;
            results[cat] = timeElapsed;
            cat++;
        }

        double linearCoefficient = 0.00085;
        double theoreticalValue = linearCoefficient * N;

        printf("%d\t\t%.4lf\t\t%.4lf\t\t%.4lf\t\t%.4lf\t\t%.4lf\n", 
               N, results[1], results[2], results[3], results[4], theoreticalValue);
    }

    free(expressionBuffer);
    return 0;
}