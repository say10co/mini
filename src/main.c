#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/lexer.h"
#include "../include/token.h"
#include "../include/parser.h"
#include "../include/execution.h"

void debug_print_token(t_token *token)
{
    if(!token)
        printf("null\n");
    else
        printf("value = %s &&  type = %d\n",token->value, token->type );
}
void deallocate(t_list *list)
{
     t_list *curr = list;
     t_list *tmp;
    
    while(curr)
    {
        free(curr->content);
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}
void print_tokens(t_list *list)
{
    t_list * curr = list;
    while(curr)
    {
        debug_print_token((t_token *) curr->content);
        curr = curr->next;
    }
}
void print_cmd(t_list *list)
{
    int i = 0;
    t_parser *curr = (t_parser *)malloc(sizeof(t_parser ));
        while(list)
        {
               curr = (t_parser *)list->content;
                i = 0;
                while(curr->cmd[i])
                {
                    printf("cmd [%d] = %s\n",i,curr->cmd[i]);
                    i++;
                }
             printf("in_file =  %d && out_file = %d\n", curr->in_fd,curr->out_fd);
            list = list->next;
        }
}
int main()
{
    char *str;
    t_list *tokens;
    t_list  *cmd;

    cmd = NULL;
    while(1)
    {
            
         str = readline("➜ minishell ");
        if(!(str[0] != '\0'))
            continue;
         add_history(str);
         tokens = lexer(str);
        if(check_syntax(tokens))
        {
            deallocate(tokens);
            continue; 
        }

       cmd = fill_command(tokens);
       
       // print_cmd(cmd);
            //execution//
           execut(cmd);


	   // print_tokens(tokens);
           // parser(tokens);
          deallocate(tokens);
    }
    return 0;
}
