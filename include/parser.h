#ifndef PARSER_H
#define PARSER_H
#include "../lib_ft/libft.h"
  #include <fcntl.h>
typedef struct s_parser
{
    char    **cmd;
    int     in_fd;
    int    out_fd;
    struct s_parser *next;
}t_parser;

int check_syntax(t_list *tokens);
void init_parser(t_parser *cmd);
t_list *fill_command(t_list *tokens);

#endif
