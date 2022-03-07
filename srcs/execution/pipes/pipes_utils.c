/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:48 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/04 17:49:49 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	nb_cmds(t_cmd *cmd)
{
	int	j;

	j = 0;
	while (cmd)
	{
		cmd = cmd->next;
		j++;
	}
	return (j);
}

void	safely_pipe_me(int new_pipe_fd[])
{
	if ((pipe(new_pipe_fd)) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	safely_fork(int *pid)
{
	*pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
