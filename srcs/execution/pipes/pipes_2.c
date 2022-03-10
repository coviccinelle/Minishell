/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:19 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/10 18:40:31 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	dup_last_file_fd_out(t_cmd *cmd);
int	dup_last_file_fd_in(t_cmd *cmd);

void	child_process(t_cmd *cmd, int *fd, char ***env)
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
			nb_tabs(cmd->av), cmd->av, env);
		exit(g_exit_value);
	}
	else if (!is_builtin(cmd->av[0]))
	{
		g_exit_value = exec_cmd(nb_tabs(cmd->av), cmd->av, env);
		exit(g_exit_value);
	}
}

void	waiting_for_all_children_to_finish_executionn(t_cmd *cmd)
{
	int	status;

	dup2(STDOUT, STDIN);
	if (!cmd)
		fprintf(stderr, "\n DONT exist\n");
	while (cmd)
	{
		fprintf(stderr, "\n CMD %s \n", cmd->av[0]);
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
		cmd = cmd->next;
	}
}

void	close_old_prepare_eventual_new(t_cmd *cmd, int *fd)
{
	close(WRITE_END);
	if (cmd->next)
		dup2(READ_END, STDIN);
	close(READ_END);
}

void	run_piped_cmds(t_mini *mini, char ***env)
{
	t_cmd	*cmd;
	int		fd[2];
	int		j;

	j = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		g_exit_value = 0;
		safely_pipe_me(fd);
		safely_fork(&(cmd->pid));
		ft_disable_if_fork(cmd->pid);
		if (cmd->pid == 0)
		{
			child_process(cmd, fd, env);
		}
		else
			close_old_prepare_eventual_new(cmd, fd);
		close(READ_END);
		close(WRITE_END);
		cmd = cmd->next;
		j++;
	}
	waiting_for_all_children_to_finish_executionn(mini->cmd);
	ft_start_signal();
}
