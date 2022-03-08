/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_search_and_execution.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:05:06 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/08 17:11:37 by thi-phng         ###   ########.fr       */
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
		exec_cd(ac, av, *env);
	if (!(ft_strcmp(builtin, "echo")))
		exit_status = exec_echo(ac, av);
	if (!(ft_strcmp(builtin, "env")))
		print_env(*env);
	if (!(ft_strcmp(builtin, "export")))
		exit_status = exec_export(ac, av, env);
	if (!(ft_strcmp(builtin, "exit")))
		exec_exit(ac, av);
	if (!(ft_strcmp(builtin, "pwd")))
		exit_status = exec_pwd();
	if (!(ft_strcmp(builtin, "unset")))
		exit_status = exec_unset(ac, av, env);
	return (exit_status);
}

char	*ft_strxjoin(char *s1, char *s2, char *s3)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

char	**ft_split(char *s, char sep)
{
	char	**tab;
	int		nb_tabs;
	int		i;
	int		j;

	nb_tabs = 0;
	j = -1;
	while (s[++j])
		if (s[j] == sep)
			nb_tabs++;
	tab = malloc(sizeof(char *) * (nb_tabs + 2));
	tab[nb_tabs + 1] = NULL;
	j = 0;
	while (j < nb_tabs + 1)
	{
		i = 0;
		while (s[i] && s[i] != sep)
			i++;
		tab[j++] = ft_strndup(s, i);
		s = &s[i + 1];
	}
	return (tab);
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
	if (!cmd)
		return (NULL);
	path = ft_split(possible_paths, ':');
	free(possible_paths);
	while (path[++j])
	{
		absolute_path = ft_strxjoin(path[j], "/", cmd);
		if (stat(absolute_path, &s) == 0)
		{
			free_tab(&path);
			return (absolute_path);
		}
		ft_memdel(&absolute_path);
	}
	free_tab(&path);
	ft_memdel(&absolute_path);
	return (NULL);
}

void	safely_exec_bin_cmds(char *path, char **av,
				char **env, int *exit_status)
{
	if (execve(path, av, env) < 0)
	{
		perror(path);
		*exit_status = 1;
	}
}

int	exec_cmd(int ac, char **av, char ***env)
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
		exit_status = 127;
	}
	else if (path != NULL)
		safely_exec_bin_cmds(path, av, *env, &exit_status);
	free(path);
	return (exit_status);
}
