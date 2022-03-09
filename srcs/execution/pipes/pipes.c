/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:19 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/09 21:39:54 by thi-phng         ###   ########.fr       */
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

void	i_am_your_father(t_cmd *cmd, char ***env)
{
	if (cmp_them_all(cmd) == 0)
		g_exit_value = exec_builtin(cmd->av[0], \
			nb_tabs(cmd->av), cmd->av, env);
}

// built in 
// cmd invalid dans les non built in

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
		i_am_your_father(cmd, env);
	}
	else
	{
		if (dup_last_file_fd_in(cmd) == 1)
			exit (1);
		fd_out = dup_last_file_fd_out(cmd);
		if (cmp_again(cmd) == 0)
			ret = (exec_builtin(cmd->av[0], \
				nb_tabs(cmd->av), cmd->av, env));
		close(fd_out);
		exit(ret); 
		//free(&(env));
	}
	return (g_exit_value);
}

int	exec_cmd_with_no_pipe(t_mini *mini, char ***env)
{
	t_cmd	*cmd;
	int		status;
//	int		exit_value;
//	pid_t	father;

	g_exit_value = 0;
	cmd = mini->cmd;
	if (is_builtin(cmd->av[0]))
		g_exit_value = exec_builtin_no_pipe(mini, env);
	else
	{
		cmd->pid = fork();
		ft_disable_if_fork(cmd->pid);
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if(WIFEXITED(status))
				g_exit_value = WEXITSTATUS(status);
			fprintf(stderr, "\n  g_ret = %d\n", g_exit_value);
		}
		if (cmd->pid == 0)
		{
			if (dup_last_file_fd_in(cmd) == 1)
				exit (1);
			dup_last_file_fd_out(cmd);
			exit(exec_cmd(nb_tabs(cmd->av), cmd->av, env));
			//if(WIFEXITED(status))
			//	g_exit_value = WEXITSTATUS(status);
			//fprintf(stderr, "\n  g_ret = %d\n", g_exit_value);
			//exit(g_exit_value);
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

void		child_process(t_cmd *cmd, int *fd, char ***env)
{
	close(READ_END);
	if (dup_last_file_fd_in(cmd) == 1)
		exit (1); //return?
	if (cmd->next)
		dup2(WRITE_END, STDOUT);
	if (dup_last_file_fd_out(cmd) == 1)
		exit (1); //return?
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

	if(!cmd)
		fprintf(stderr, "\n DONT exist\n");
	while (cmd)
	{
		fprintf(stderr, "\n CMD %s \n", cmd->av[0]);
		waitpid(cmd->pid, &status, 0);
		if(WIFEXITED(status))
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

void	run_piped_cmds(t_mini *mini, int nb_cmd, char ***env)
{
	t_cmd	*cmd;
	int		fd[2];
//	pid_t	new_pid;
	(void)nb_cmd;
	int		j;

	j = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		g_exit_value = 0;
		safely_pipe_me(fd);
		safely_fork(&(cmd->pid));
		ft_disable_if_fork(cmd->pid);
		fprintf(stderr, "\n GRET AVANT = %d \n", g_exit_value);
		if (cmd->pid == 0)
		{
			child_process(cmd, fd, env);
			fprintf(stderr, "\n EST CE QUE C A A EXIT ? \n");
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
	fprintf(stderr, "\n GRET FINAL = %d\n", g_exit_value);
}
