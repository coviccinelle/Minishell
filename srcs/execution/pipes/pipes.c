/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:19 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/13 21:37:16 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	dup_last_file_fd_out(t_cmd *cmd);
int	dup_last_file_fd_in(t_cmd *cmd);

char	*ft_readline_heredoc(char *line)
{
	line = readline(">");
	if (!line)
	{
		printf("\b\b  \b\b\n> bash: warning: here-document delimited \
				by end-of-file (wanted `EOF')\n\n");
		return (NULL);
	}
	return (line);
}

void	call_heredoc(char *eof)
{
	int		fd;
	char	*input;

	input = NULL;
	if (eof == NULL)
		return ;
	fd = open("heredoc", O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror(eof);
	while (1)
	{
		input = ft_readline_heredoc(input);
		if (input)
		{
			if (ft_strcmp(input, eof) != 0)
				ft_putendl_fd(input, fd);
			if (ft_strcmp(input, eof) == 0)
				break ;
			free(input);
		}
		else
			break ;
	}
	close(fd);
}

int	cmp_them_all(t_cmd *cmd)
{
	int	ret;

	ret = -1;
	ret = ft_strcmp(cmd->av[0], "export");
	if (ret == 0)
		return (ret);
	ret = ft_strcmp(cmd->av[0], "unset");
	if (ret == 0)
		return (ret);
	ret = ft_strcmp(cmd->av[0], "exit");
	if (ret == 0)
		return (ret);
	ret = ft_strcmp(cmd->av[0], "cd");
	if (ret == 0)
		return (ret);
	ret = ft_strcmp(cmd->av[0], "env");
	if (ret == 0)
		return (ret);
	return (ret);
}

int	cmp_again(t_cmd *cmd)
{
	int	ret;

	ret = -1;
	ret = ft_strcmp(cmd->av[0], "echo");
	if (ret == 0)
		return (ret);
	ret = ft_strcmp(cmd->av[0], "pwd");
	if (ret == 0)
		return (ret);
	return (ret);
}

void	i_am_your_father(t_mini *mini, t_cmd *cmd, char ***env)
{
	char	**avv = ft_copy_tab(cmd->av);
	int	ntabs = nb_tabs(avv);
	if (cmp_them_all(cmd) == 0)
	{
		if (ft_strcmp(avv[0], "exit") == 0)
		{
			free_tout_mini(mini);
			free(mini);
			free_tab(env);
			g_exit_value = exec_builtin("exit", \
			ntabs, avv, env);
		}
		else
			g_exit_value = exec_builtin(avv[0], \
				ntabs, avv, env);
	}
}
