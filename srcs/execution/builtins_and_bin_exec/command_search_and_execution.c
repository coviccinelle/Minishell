/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_search_and_execution.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:05:06 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/14 17:26:18 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <sys/wait.h>

int	is_builtin(char *builtin)
{
	if (!(ft_strcmp(builtin, "cd")))
		return (1);
	if (!(ft_strcmp(builtin, "echo")))
		return (1);
	if (!(ft_strcmp(builtin, "env")))
		return (1);
	if (!(ft_strcmp(builtin, "export")))
		return (1);
	if (!(ft_strcmp(builtin, "exit")))
		return (1);
	if (!(ft_strcmp(builtin, "pwd")))
		return (1);
	if (!(ft_strcmp(builtin, "unset")))
		return (1);
	return (0);
}

int	exec_builtin(char *builtin, int ac, char **av, char ***env)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (!(ft_strcmp(builtin, "cd")))
		exit_status = exec_cd(ac, av, env);
	if (!(ft_strcmp(builtin, "echo")))
		exit_status = exec_echo(ac, av);
	if (!(ft_strcmp(builtin, "env")))
		exit_status = print_env(*env);
	if (!(ft_strcmp(builtin, "export")))
		exit_status = exec_export(ac, av, env);
	if (!(ft_strcmp(builtin, "exit")))
		exit_status = exec_exit(ac, av, &exit_status);
	if (!(ft_strcmp(builtin, "pwd")))
		exit_status = exec_pwd();
	if (!(ft_strcmp(builtin, "unset")))
		exit_status = exec_unset(ac, av, env);
	return (exit_status);
}

int	path_is_unset(char **possible_paths, char *cmd)
{
	if (!ft_strcmp(*possible_paths, ""))
	{
		free(*possible_paths);
		perror(cmd);
		return (127);
	}
	return (0);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char		**path;
	char		*absolute_path;
	int			j;
	struct stat	s;
	char		*possible_paths;

	possible_paths = ft_getenv(env, "PATH");
	j = -1;
	if ((path_is_unset(&possible_paths, cmd)) == 127)
		exit(127);
	path = ft_split(possible_paths, ':');
	free(possible_paths);
	while (path[++j])
	{
		absolute_path = ft_strxjoin(path[j], "/", cmd);
		if (stat(absolute_path, &s) == 0)
		{
			free_tab_3(path, nb_tabs(path));
			return (absolute_path);
		}
		ft_memdel(&absolute_path);
	}
	free_tab_3(path, nb_tabs(path));
	ft_memdel(&absolute_path);
	return (NULL);
}

int	exec_cmd(int ac, char **av, char ***env, t_mini *mini)
{
	char	*path;
	int		relative;
	int		exit_status;

	(void)ac;
	path = NULL;
	relative = 0;
	exit_status = 0;
	if ((access(av[0], F_OK)) == 0)
	{
		relative = 1;
		path = ft_strdup(av[0]);
	}
	if (relative == 0)
		path = find_cmd_path(av[0], *env);
	if (path == NULL)
	{
		ft_puterror_fd("minishell: ", "command not found: ", av[0]);
		free_child(mini, env);
		exit(127);
	}
	else if (path != NULL)
		safely_exec_bin_cmds(path, av, *env, &exit_status);
	free(path);
	return (exit_status);
}
