/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yomari <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:17:32 by yomari            #+#    #+#             */
/*   Updated: 2023/01/23 23:23:04 by yomari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../lib_ft/libft.h"
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "../include/parser.h"
#include<readline/readline.h>

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

	if (lp == 0)
		printf("\n");
}

void	cd(t_parser *list)
{
	chdir(list->cmd[1]);
}
void	pwd(void)
{
	char cwd[PATH_MAX];
	if ( getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n" ,cwd);
}

void	get_fds_from_pipes(int **pie, int size)
{
	int	i;

	i = 0;
	while(i < size)
		pipe(pie[i++]);
}

void	execute(t_list *cmds)
{
	int	size =ft_lstsize(cmds);

	int	fd[size + 1][2];
	int	pid[size];
	int	i;
	int	j;
//	char buffer[100];
	t_parser *tmp;
	
	i = 0;
	while (i < size )
		pipe(fd[i++]);
	tmp =(t_parser *) malloc(sizeof(t_parser));
	i = 0;
	while (i < size && cmds)
	{
		tmp = (t_parser *) cmds->content;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (size > 1)
			{
			j = 0;
			while (j < size )
			{
				if (i != j)
					close(fd[j][0]);
				if (i + 1 !=j)
					close(fd[j][1]);
				j++;
			}
			if (cmds->next)
			{
				if ( i > 0)
				{
					//printf("hello before %d \n", i);
					dup2(fd[i][0], STDIN_FILENO);
				}
				dup2(fd[i + 1][1], STDOUT_FILENO );
					//printf("hello after %d \n", i);
			}
			if (!cmds->next)
			{
				//	printf("hello eee %d \n", i);
				dup2(fd[i][0], STDIN_FILENO);
			//	dup2(fd[size][1], STDOUT_FILENO );
			//	read(fd[i][0], buffer, 100);
			//		printf("  hada li bit %s\n whada kifach blano \n", buffer);
			}
			}
			execve(tmp->cmd[0], tmp->cmd, NULL);
		}
		close(fd[i][0]);
		if (i + 1 != size)
			close(fd[i + 1][1]);
		cmds= cmds->next;
		i++;
	}
		while (i-- > 0)
			wait(NULL);
}
int	start(t_list *list)
{
	if (ft_lstsize(list) > 0)
		execute(list);
	else
		return(1);
	return(0);
}
