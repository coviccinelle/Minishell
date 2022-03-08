/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:25:53 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/08 18:49:46 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		//ft_memdel(&pwd);
		if(pwd)
			free(pwd);
		return (EXIT_SUCCESS);
	}
	else if (!pwd)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	init_and_getcwd(int *res, char **new_path,
				char **new_pwd, char **current_path)
{
	*res = 0;
	*new_path = NULL;
	*new_pwd = NULL;
	*current_path = getcwd(NULL, 0);
}

int	error_case(char **new_pwd, char **av, int res)
{
	*new_pwd = getcwd(NULL, 0);
	if (res == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(av[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_pwds(char **current_path, char **new_path)
{
	free(*current_path);
	free(*new_path);
}

int	exec_cd(int ac, char **av, char **env)
{
	char	*current_path;
	char	*new_path;
	char	*new_pwd;
	int		res;

	init_and_getcwd(&res, &new_path, &new_pwd, &current_path);
	if (ac > 2)
		return (ft_puterror_fd("minishell: ",
				"cd: ", "too many arguments"));
	if ((ac == 1) || (ac == 2 && (!ft_strncmp(av[1], "~", ft_strlen("~")))))
		new_path = ft_getenv(env, "HOME");
	else if (ac == 2 && (!ft_strncmp(av[1], "-", ft_strlen("-"))))
	{
		new_path = ft_getenv(env, "OLDPWD");
		printf("%s\n", new_path);
	}
	else
		new_path = av[1];
	res = chdir(new_path);
	if (error_case(&new_pwd, av, res) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_setenv(&env, NULL, "PWD", new_pwd);
	ft_setenv(&env, NULL, "OLDPWD", current_path);
	free_pwds(&current_path, &new_path);
	return (EXIT_SUCCESS);
}
