/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:11:08 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/15 12:05:34 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*new_elem_cmd(t_mini *mini)
{
	t_cmd	*elem;

	(void)mini;
	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->av = NULL;
	elem->la = NULL;
	elem->type = 0;
	elem->file_in = NULL;
	elem->file_out = NULL;
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
}

int	create_files(int type, char *filename)
{
	int	fd;

	fd = -1;
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

//stock cmd 
//if !cmd -> return NULL to protect -> norme
t_cmd	*stock_cmds(t_mini *mini, char ***env)
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
			if (ft_each_cmd_4(mini, &i, &cmd, env))
				stock_cmds_3(cmd);
			else
			{
				free(cmd);
				return (NULL);
			}
		}
		if (mini->line[i] && mini->line[i] == '|')
			i++;
	}
	return (cmd_lst);
}
