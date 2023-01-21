
#include "../include/execution.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/token.h"
void ft_free(char **t)
{
	int i = -1;
	while(t[++i])
		free(t[i]);
}
char **realloc_cmd(char **cmd,char *str)
{
	char **tmp;
	int i = 0;

	if(!cmd[0])
		cmd[0] = ft_strdup(str);
	else
	{
		while(cmd[i])
			i++;
		tmp = (char **)malloc(sizeof(char *) * (i +1));
		i = 0;	
		while(cmd[i])
		{	
			tmp[i] = ft_strdup(cmd[i]);
			i++;
		}
		tmp[i] = NULL;
		cmd = (char **) malloc(sizeof(char * ) * (i + 2));
		i = 0;
		while(tmp[i])
		{	
			cmd[i] = tmp[i];
			i++;
		}
		cmd[i] = ft_strdup(str);
		cmd [i + 1]= NULL;
	}
	return (cmd);
}
t_list *fill_command(t_list *tokens)
{
	t_list	*cmd_list;
	t_parser *content;
	t_token		*curr;
	int flag = 0;

	cmd_list = NULL;
	
	content = (t_parser *)malloc(sizeof(t_parser));
	content->in_fd = 0;
	content->out_fd = 1;
	content->cmd = (char **)malloc(sizeof(char * ) * 2);
	content->cmd[0] = NULL;
	content->cmd[1] = NULL;
	
	curr = (t_token *) tokens->content;
	
	while(curr->type != TOKEN_EOF)
	{
		if(curr->type == TOKEN_STRING)
			content->cmd = realloc_cmd(content->cmd,curr->value);
		else if(curr->type == TOKEN_REDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
	
			if(curr->type == TOKEN_STRING )
				content->out_fd = open(curr->value,O_CREAT | O_RDWR , 0664);
		}
		else if(curr->type == TOKEN_LREDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if(curr->type == TOKEN_STRING )
				content->in_fd = open(curr->value,O_CREAT | O_RDWR, 0664);
		}
		else if(curr->type == TOKEN_PIPE)
		{
			 flag = 1;
			  ft_lstadd_back(&cmd_list, ft_lstnew(content));
			content = (t_parser *)malloc(sizeof(t_parser));
			content->in_fd = 0;
			content->out_fd = 1;
		
			content->cmd = (char **)malloc(sizeof(char * ) * 2);
			content->cmd[0] = NULL;
			content->cmd[1] = NULL;
	  
		}
		
		tokens = tokens->next;
		curr = (t_token *) tokens->content;

	}
	 ft_lstadd_back(&cmd_list, ft_lstnew(content));

	return (cmd_list);

}
char *string_parser(char *str)
{
	int i;
	char *string;

	i = 0; 
	string = NULL;
	if((str[0] == '\"' && str[1] == '\"') || (str[0] == '\'' && str[1] == '\'' ))
		return ("\0");
	while(str[i])
	{
	 	if(str[i] == '\"')
		{
			i++;
			while(str[i] && str[i] != '\"')
			{
				string = append_to_str(string,str[i]);
				i++;
			}
			if(str[i] == '\0')
				return (NULL);
			i++;
		}
		else if(str[i] == '\'')
		{	
			i++;
			while(str[i] && str[i] != '\'')
			{
				string = append_to_str(string,str[i]);
				i++;
			}
			if(str[i] == '\0')
				return (NULL);
			i++;
		}
		else
		{
			string = append_to_str(string,str[i]);
			i++;
		}
	 }
	return (string);
}             


int check_syntax(t_list *tokens)
{
        // t_parser *cmd;
        t_token *curr;
        t_token *next;
        //char **args;
       
        curr = (t_token *) tokens->content;
        next = (t_token *) tokens->next->content;
        
        if(curr->type == TOKEN_PIPE)
           return(printf("minishell: syntax error unexpected token `|'\n"));
        while(curr->type != TOKEN_EOF)
        {

            if(curr->type == TOKEN_PIPE && next->type == TOKEN_REDIRECT)
            {
                curr = (t_token *) tokens->content;
                next = (t_token *) tokens->next->content;
            }
            else if(curr->type == TOKEN_STRING )
			{
				char *temp_value = curr->value;
                char *str = string_parser(curr->value);
				
	    		if (str == NULL)
           			return(printf("minishell: syntax error unexpected token `\\n'\n"));

                if (str != temp_value)
                	free(temp_value);

        	    curr->value = str;
			} 
            else if(curr->type != TOKEN_STRING && next->type != TOKEN_STRING)
                return(printf("minishell: syntax error unexpected token `%s'\n",next->value));
            
			//debug_print_token(curr);
          tokens = tokens->next;
          curr = (t_token *) tokens->content;
		  if(curr->type != TOKEN_EOF)
			next = (t_token *) tokens->next->content;
        }
        if(curr->type == TOKEN_REDIRECT )
            return(printf("minishell: syntax error near unexpected token `newline'\n"));
        return 0;
}
