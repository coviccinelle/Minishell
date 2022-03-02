/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:25:53 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/02 15:10:39 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int exec_pwd(void) 
{
	char *pwd;

	pwd = getcwd(NULL, 0); // si sur linux sinon il faut remplacer NULL et 0
	if (pwd)
	{
		ft_putendl_fd(pwd, 1); //Si la taille du chemin absolu du répertoire de travail en cours, caractère nul de fin compris, dépasse size octets, la fonction renvoie NULL et errno contient le code d'erreur ERANGE. Une application doit détecter cette erreur et allouer un tampon plus grand si besoin est.
		ft_memdel(&pwd);
		return (EXIT_SUCCESS);
	}
	else if (!pwd)
		return (EXIT_FAILURE); 
	//update it to env PWD=
	return (EXIT_SUCCESS);
}

int	exec_cd(int ac, char **av, char **env)
{
	char	*current_path;
	char	*new_path;
	char	*new_pwd;
	int	res;

	res = 0;
	new_path = NULL;
	new_pwd = NULL;
	current_path = getcwd(NULL, 0);
	if (ac > 2)
		return (ft_puterror_fd("minishell: ", "cd: ", "too many arguments")); //donc ret EXIT a 1 aka exit failure
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
	new_pwd = getcwd(NULL, 0);
	if (res == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(av[1]); // no such file or directory, not a directory...
		return (EXIT_FAILURE);
	}
	ft_setenv(&env, NULL, "PWD", new_pwd);
	ft_setenv(&env, NULL, "OLDPWD", current_path);
	return (EXIT_SUCCESS);
}

