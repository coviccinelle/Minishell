/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:11:08 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/08 18:26:38 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*new_elem_cmd(t_mini *mini)
{
	t_cmd	*elem;

	(void)mini;//to free after only
	elem = malloc(sizeof(t_cmd));
	if (!elem)
		//exit_custom(mini, NULL, AUTO);
		printf("Exist and Free mini\n");
	//elem->line = NULL;
	elem->av = NULL;
	elem->type = NOPE;
	elem->type = 0;
	elem->file_in = NULL;
	elem->file_out = NULL;
//	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	add_cmd(t_cmd **cmd_lst, t_cmd *cmd)
{
	t_cmd	*current;

	if (!(*cmd_lst))
	{
		*cmd_lst = cmd;
		return ;
	}
	current = *cmd_lst;
	while (current->next)
		current = current->next;
	current->next = cmd;
	//cmd->prev = current;
}

int	create_files(int type, char *filename)
{
	int	fd;

	fd = -1;
	printf("type de ficher = %d\n", type);
	if (type == TRUNC_0)
		fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type == APPEND_0)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
		return (1);
	}
	close(fd);
	return (0);
}

void	stock_cmds_3(t_cmd *cmd)
{
	t_file	*file_out;
	t_file	*file_inn;

	file_inn = cmd->file_in;
	file_out = cmd->file_out;
	while ((cmd)->file_in)
	{
		create_files((*cmd).file_in->type, (cmd)->file_in->name);
		(cmd)->file_in = (cmd)->file_in->next;
	}
	while ((cmd)->file_out)
	{
		create_files((*cmd).file_out->type, (cmd)->file_out->name);
		(cmd)->file_out = (cmd)->file_out->next;
	}
	cmd->last_file_in = ft_last_file(file_inn);
	cmd->last_file_out = ft_last_file(file_out);
}

void	ft_free_c(t_cmd **c)
{
	t_cmd	*temp;

	while((*c))
	{
		temp = (*c)->next;
		free((*c));
		(*c) = temp;
	}
}


//stock cmd
t_cmd	*stock_cmds(t_mini *mini)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd_lst = NULL;
	i = 0;
	cmd = NULL;
	while (mini->line[i])
	{
		cmd = new_elem_cmd(mini);
		add_cmd(&cmd_lst, cmd);
		while (mini->line[i] && mini->line[i] != '|')
		{
			while (mini->line[i] == ' ')
				i++;
			int a = ft_each_cmd_4(mini, mini->line, &i, &cmd);
			if (a == 1)
				stock_cmds_3(cmd);
			else
			{
				printf("ERROR: syntax error => free tout\n\n");
				return (NULL);
			}
		}
		if (mini->line[i] == '|')
			i++;
		//if(cmd)
		//	ft_free_c(&cmd);
	}
	return (cmd_lst);
}
