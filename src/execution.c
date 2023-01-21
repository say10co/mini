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

int builtins(t_parser *list)
{
	if(!ft_strncmp(list->cmd[0],"echo",5)) 
		echo(list);
	else if(!ft_strncmp(list->cmd[0],"cd",3)) 
		echo(list);
	else if(!ft_strncmp(list->cmd[0],"pwd",4)) 
		echo(list);
	else if(!ft_strncmp(list->cmd[0],"export",7)) 
		echo(list);
	else if(!ft_strncmp(list->cmd[0],"unset",6)) 
		echo(list);
	else if(!ft_strncmp(list->cmd[0],"env",4)) 
		echo(list);
	else if(!ft_strncmp(list->cmd[0],"exit",5)) 
		echo(list);
	else 
		return 1;
	return 0;
}
int execut(t_parser *list)
{
	if(!builtins(list))
			return 0;

	return 0;
}


