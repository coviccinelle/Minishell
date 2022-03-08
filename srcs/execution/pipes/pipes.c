/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:19 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/08 15:03:07 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <string.h>

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
			if (ft_strncmp(input, eof, strlen(eof)) != 0)
				ft_putendl_fd(input, fd);
			if (ft_strncmp(input, eof, strlen(eof)) == 0)
				break ;
			free(input);
		}
		else
			break ;
	}
	close(fd);
}

int	exec_builtin_no_pipe(t_mini *mini)
{
	t_cmd	*cmd;
	pid_t	f;
	int		status;
	int		fd_out;

	cmd = mini->cmd;
	f = fork();
	if (f != 0)
	{
		waitpid(f, &status, 0);
		if ((ft_strcmp(cmd->av[0], "export") == 0) \
				|| (ft_strcmp(cmd->av[0], "unset") == 0 && cmd->av[1]) \
				|| ft_strcmp(cmd->av[0], "exit") == 0 \
				|| ft_strcmp(cmd->av[0], "cd") == 0 \
				|| ft_strcmp(cmd->av[0], "env") == 0)
			g_exit_value = exec_builtin(cmd->av[0], \
				nb_tabs(cmd->av), cmd->av, &mini->env);
	}
	else
	{
		if (dup_last_file_fd_in(cmd) == 1)
			exit (1);
		fd_out = dup_last_file_fd_out(cmd);
		if (ft_strcmp(cmd->av[0], "echo") == 0 \
					|| ft_strcmp(cmd->av[0], "pwd") == 0)
			g_exit_value = exec_builtin(cmd->av[0], \
				nb_tabs(cmd->av), cmd->av, &mini->env);
		close(fd_out);
		exit(1);
	}
	return (g_exit_value);
}

int	exec_cmd_with_no_pipe(t_mini *mini)
{
	t_cmd	*cmd;
	int		status;
	int		exit_value;
	pid_t	father;

	exit_value = 0;
	cmd = mini->cmd;
	if (is_builtin(cmd->av[0]))
		exit_value = exec_builtin_no_pipe(mini);
	else
	{
		father = fork();
		ft_disable_if_fork(father);
		if (father > 0)
			waitpid(-1, &status, 0);
		if (father == 0)
		{
			if (dup_last_file_fd_in(cmd) == 1)
				exit (1);
			dup_last_file_fd_out(cmd);
			exit_value = exec_cmd(nb_tabs(cmd->av), cmd->av, &mini->env);
			exit(0);
		}
	}
	return (g_exit_value);
}

int	dup_last_file_fd_in(t_cmd *cmd)
{
	t_file	*last_file_in;
	int		last_file;

	last_file = 0;
	last_file_in = cmd->last_file_in;
	if (cmd->last_file_in == NULL)
		return (0);
	if (last_file_in->type == HEREDOC)
		last_file = open("heredoc", O_RDONLY);
	else
		last_file = open(last_file_in->name, O_RDONLY);
	if (last_file == -1)
	{
		perror(last_file_in->name);
		return (1);
	}
	dup2(last_file, 0);
	close(last_file);
	unlink("heredoc");
	return (0);
}

int	dup_last_file_fd_out(t_cmd *cmd)
{
	t_file	*last_file_out;
	int		last_file;

	last_file = 0;
	last_file_out = cmd->last_file_out;
	if (cmd->last_file_out == NULL)
		return (0);
	if (last_file_out->type == TRUNC_0)
		last_file = open(last_file_out->name, \
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (last_file_out->type == APPEND_0)
		last_file = open(last_file_out->name, \
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (last_file == -1)
	{
		perror(last_file_out->name);
		return (1);
	}
	dup2(last_file, STDOUT);
	return (last_file);
}

void	child_process(t_cmd *cmd, int *fd, t_mini *mini)
{
	close(READ_END);
	if (dup_last_file_fd_in(cmd) == 1)
		exit (1);
	if (cmd->next)
		dup2(WRITE_END, STDOUT);
	if (dup_last_file_fd_out(cmd) == 1)
		exit (1);
	close(WRITE_END);
	if (is_builtin(cmd->av[0]))
	{
		g_exit_value = exec_builtin(cmd->av[0], \
			nb_tabs(cmd->av), cmd->av, &mini->env);
		exit(g_exit_value);
	}
	else if (!is_builtin(cmd->av[0]))
	{
		g_exit_value = exec_cmd(nb_tabs(cmd->av), cmd->av, &mini->env);
		exit(g_exit_value);
	}
}

void	waiting_for_all_children_to_finish_executionn(int nb_cmds)
{
	int	i;
	int	status;

	i = -1;
	dup2(STDOUT, STDIN);
	if (nb_cmds == 0)
		return ;
	while (i < nb_cmds)
	{
		if (waitpid(-1, &status, 0) < -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_old_prepare_eventual_new(t_cmd *cmd, int *fd)
{
	close(WRITE_END);
	if (cmd->next)
		dup2(READ_END, STDIN);
	close(READ_END);
}

void	run_piped_cmds(t_mini *mini, int nb_cmd)
{
	t_cmd	*cmd;
	int		fd[2];
	pid_t	new_pid;
	int		j;

	j = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		safely_pipe_me(fd);
		safely_fork(&new_pid);
		ft_disable_if_fork(new_pid);
		if (new_pid == 0)
			child_process(cmd, fd, mini);
		else
			close_old_prepare_eventual_new(cmd, fd);
		close(READ_END);
		close(WRITE_END);
		cmd = cmd->next;
		j++;
	}
	waiting_for_all_children_to_finish_executionn(nb_cmd);
}
