/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:19 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/14 14:16:21 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	dup_last_file_fd_out(t_cmd *cmd);
int	dup_last_file_fd_in(t_cmd *cmd);

void	free_child(t_mini *mini, char ***env)
{
	free_tout_mini(mini);
	free(mini);
	free_tab(env);
}

int	exec_builtin_no_pipe(t_mini *mini, char ***env)
{
	t_cmd	*cmd;
	pid_t	f;
	int		status;
	int		fd_out;
	int		ret;

	cmd = mini->cmd;
	f = fork();
	if (f != 0)
	{
		waitpid(f, &status, 0);
		i_am_your_father(mini, cmd, env);
	}
	else
	{
		if (dup_last_file_fd_in(cmd) == 1)
			exit (1);
		fd_out = dup_last_file_fd_out(cmd);
		if (cmp_again(cmd) == 0)
			ret = (exec_builtin(cmd->av[0], \
				nb_tabs(cmd->av), cmd->av, env));
		free_child(mini, env);
		close(fd_out);
		exit(ret);
	}
	return (g_exit_value);
}

void	father_no_pipe(t_cmd *cmd)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_value = WEXITSTATUS(status);
	//free_one_cmd(cmd);
}

int	exec_cmd_with_no_pipe(t_mini *mini, char ***env)
{
	t_cmd	*cmd;

	g_exit_value = 0;
	cmd = mini->cmd;
	if (is_builtin(cmd->av[0]))
		g_exit_value = exec_builtin_no_pipe(mini, env);
	else
	{
		cmd->pid = fork();
		ft_disable_if_fork(cmd->pid);
		if (cmd->pid > 0)
			father_no_pipe(cmd);
		if (cmd->pid == 0)
		{
			if (dup_last_file_fd_in(cmd) == 1)
				exit (1);
			dup_last_file_fd_out(cmd);
			exit(exec_cmd(nb_tabs(cmd->av), cmd->av, env, mini));
		}
	}
	ft_start_signal();
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
