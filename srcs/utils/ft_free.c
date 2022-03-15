/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:09:01 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/15 11:39:05 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab2(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	tab = NULL;
}

void	free_t_file(t_file **f)
{
	t_file	*temp;

	while (*f)
	{
		temp = (*f)->next;
		if ((*f)->name)
			free ((*f)->name);
		(*f) = temp;
	}
}

void	free_one_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->av)
		free_tab_3((cmd->av), nb_tabs(cmd->av));
	if (cmd->la)
		free(cmd->la);
	if (cmd->file_in)
		free_t_file(&(cmd->file_in));
	if (cmd->file_out)
		free_t_file(&(cmd->file_out));
}

void	ft_free_cmds(t_mini *mini)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = mini->cmd;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->av)
			free_tab_3((cmd->av), nb_tabs(cmd->av));
		if (cmd->file_in)
			free_t_file(&(cmd->file_in));
		if (cmd->file_out)
			free_t_file(&(cmd->file_out));
		if (cmd->last_file_in)
			free(cmd->last_file_in);
		if (cmd->last_file_out)
			free(cmd->last_file_out->name);
		if (cmd->last_file_out)
			free(cmd->last_file_out);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp)
			free(tmp);
	}
}

void	free_tout_mini(t_mini *mini)
{
	if (!mini)
		return ;
	else if (mini)
	{
		ft_free_cmds(mini);
		free(mini->line);
	}
}
