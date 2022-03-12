/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:48 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/10 18:23:21 by thi-phng         ###   ########.fr       */
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
	if (*pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	safely_exec_bin_cmds(char *path, char **av, \
				char **env, int *exit_status)
{
	if (execve(path, av, env) < 0)
	{
		perror(path);
		*exit_status = 1;
	}
}

char	*ft_strxjoin(char *s1, char *s2, char *s3)
{
	char	*new;
	char 	*leak;

	new = NULL;
	new	= ft_strjoin(s1, s2);
	if (!new)
		return (NULL);
	leak = new;
	new = ft_strjoin(new, s3);
	free(leak);
	return (new);
}
