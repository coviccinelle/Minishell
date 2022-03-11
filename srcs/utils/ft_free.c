/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:09:01 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/11 10:35:19 by thi-phng         ###   ########.fr       */
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
	// if (cmd)
	// 	free(cmd);
}

void	ft_free_cmds(t_mini *mini)
{
	t_cmd	*cmd;
//	t_cmd	*next;

	cmd = mini->cmd;
	if (!cmd)
		return ;
	while (cmd)
	{
	//	next = cmd->next;
		if (cmd->av)
			free_tab_3((cmd->av), nb_tabs(cmd->av));
		if (cmd->file_in)
			free_t_file(&(cmd->file_in));
		if (cmd->file_out)
			free_t_file(&(cmd->file_out));
		if (cmd)
			free(cmd);
		cmd = cmd->next;
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
