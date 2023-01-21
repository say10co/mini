#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include "../lib_ft/libft.h"

typedef struct s_lexer
{
    char *src;
    int index;
    char c;
}t_lexer;

#include "../include/token.h"
void init_lexer(t_lexer *lexer ,char *src);
void lexer_next(t_lexer * lexer);
void skip_spaces(t_lexer *lexer);
char *append_to_str(char *str , char c);
t_list *lexer(char *src);




#endif
