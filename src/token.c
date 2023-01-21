#include "../include/execution.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/token.h"

t_token *init_token(char *value, int type)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    if(!token)
        return NULL;
    token->value = value;
    token->type = type;
    return (token);
}

t_token *get_token(t_lexer *lexer)
{
    t_token *token; 
    char *s ;
    bool flag = 0; 
    
    s = NULL;
    skip_spaces(lexer);
    while((lexer->c != '\0')  && (!istoken(lexer->c) || flag))
    {
        if (lexer->c == '\"')
            flag = !flag;
        s = append_to_str(s,lexer->c);
        lexer_next(lexer);
    }
    if(s)
      token =  init_token (s,TOKEN_STRING);
    else
        token = _switch(lexer);
    return token;
}

int istoken(char c)
{
    if(c == '>' || c == '<' ||  c == '|' || c == '\0' || c == ' ')
        return 1;
    return 0;
}

t_token *_switch(t_lexer *lexer)
{
    if(lexer->c == '>')
    { 
          lexer_next(lexer);
          if(lexer->c == '>')
          {
             lexer_next(lexer);
            return init_token(">>",TOKEN_APPEND );
          }
         return init_token(">",TOKEN_REDIRECT );
    }   
    if(lexer->c == '<')
    {
       lexer_next(lexer);
        if(lexer->c == '<')
        {
             lexer_next(lexer);
            return init_token("<<",TOKEN_HEREDOC );
        }
        return init_token("<",TOKEN_LREDIRECT);
    }
    if(lexer->c == '|')
    {   
        lexer_next(lexer);
        return init_token("|",TOKEN_PIPE);
    }
    else
        return init_token("EOF",TOKEN_EOF); 
}
