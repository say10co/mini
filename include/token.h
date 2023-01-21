#ifndef TOKEN_H
#define TOKEN_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_token
{
    char *value;
    enum
    {
        TOKEN_STRING,
        TOKEN_REDIRECT,
        TOKEN_LREDIRECT, 
        TOKEN_APPEND,
        TOKEN_HEREDOC,
        TOKEN_PIPE,
        TOKEN_EOF,

    }type;
}t_token;



t_token *init_token(char *value, int type);
t_token *_switch(t_lexer *lexer);
t_token *get_token(t_lexer *lexer);
void debug_print_token(t_token *token);
int istoken(char c);

#endif