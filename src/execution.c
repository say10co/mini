#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/token.h"
#include "../include/execution.h"

void	echo (t_parser *list)
{
	int	lp;
	int	i;

	i = 1;	
	lp = 0;
	if (list->cmd[1] && list->cmd[1][0] == '-')
	{
		while (list->cmd[1][i])
		{
			if (list->cmd[1][i] == 'n')
			{
				if (list->cmd[1][i + 1] == '\0')
					lp = 1;
			}
			else
				break;
				i++;
		}
	}
	if (lp == 1)
		i = 2;
	else
		i = 1;
	while (list->cmd[i])
	{
		if (list->cmd[i+ 1])
			printf("%s ", list->cmd[i]);
		else
			printf("%s", list->cmd[i]);
		i++;
	}
	if (!lp)
		printf("\n");
}

int builtins(t_list *list)
{
	t_parser *curr = (t_parser *)list->content;

	if(!ft_strncmp(curr->cmd[0],"echo",5)) 
		echo(curr);
	else if(!ft_strncmp(curr->cmd[0],"cd",3)) 
		echo(curr);
	else if(!ft_strncmp(curr->cmd[0],"pwd",4)) 
		echo(curr);
	else if(!ft_strncmp(curr->cmd[0],"export",7)) 
		echo(curr);
	else if(!ft_strncmp(curr->cmd[0],"unset",6)) 
		echo(curr);
	else if(!ft_strncmp(curr->cmd[0],"env",4)) 
		echo(curr);
	else if(!ft_strncmp(curr->cmd[0],"exit",5)) 
		echo(curr);
	else 
		return 1;
	return 0;
}
int execut(t_list *list)
{
	if(!builtins(list))
			return 0;

	return 0;
}


