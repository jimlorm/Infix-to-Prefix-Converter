#ifndef TOKEN_H
#define TOKEN_H

// Type of token
typedef enum { 
    OPERAND, 
    OPERATOR, 
    PARENTHESIS,
    ERROR_TOKEN 
} TokenType;

// Token struct
typedef struct {
    TokenType type;
    union {
        int value;      
        char symbol;    
    } data;
} Token;

#endif // TOKEN_H