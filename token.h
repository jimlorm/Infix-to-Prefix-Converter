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

// Error status
typedef enum { 
    SUCCESS, 
    ERR_DIV_BY_ZERO, 
    ERR_MISMATCH_PAREN, 
    ERR_MALFORMED,
    ERR_INVALID_CHAR
} ErrorStatus;

#endif // TOKEN_H