/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:16:58 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/04 17:25:05 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_into_export_lst(char ***env, char **av, char **name, char **data)
{
	int	j;

	j = 1;
	while (j < nb_tabs(av))
	{
		if (name[j] != NULL)
		{
			ft_setenv(env, av[j], name[j], data[j]);
		}
		j++;
	}
	return (0);
}

void	free_all(char **name, char **data)
{
	int	j;

	j = 0;
	while (name[++j])
	{
		free(name[j]);
		free(data[j]);
	}
	free(name);
	free(data);
}

int	exec_export(int ac, char **av, char ***env)
{
	char			**name;
	char			**data;
	int				j;
	int				exit_value;

	exit_value = EXIT_SUCCESS;
	j = 0;
	data = malloc(sizeof(char **) * (nb_tabs(av)));
	name = malloc(sizeof(char **) * (nb_tabs(av)));
	if (ac == 1)
		return (ft_alphabetical_order_tab(*env));
	while (av[++j])
	{
		name[j] = cpy_trim(av[j], av[j][0], '=');
		if (!is_valid_var_name(name[j]))
		{
			exit_value = ft_puterror_fd("minishell: export :'", \
					av[j], "': not a valid identifier");
			name[j] = NULL;
		}
		data[j] = cpy_trim(av[j], '=', '\0');
	}
	get_into_export_lst(env, av, name, data);
//	free_all(name, data);
	return (exit_value);
}

int	ft_unsetenv(char ***env,char *name)
{
	int			pos_name;
	int			j;
	char		*found;

	found = find_in_env(*env, name, &pos_name);
	if (!found)
		return (0);
	j = pos_name;
	while ((*env)[j] && j < nb_tabs(*env))
	{
		ft_memdel(&(*env)[j]);
		if ((*env)[j + 1])
		{
			(*env)[j] = ft_strndup((*env)[j + 1], ft_strlen((*env)[j + 1]));
		}	
		j++;
	}
	return (0);
}

int	exec_unset(int ac, char **av, char ***env)
{
	int	j;

	(void)ac;
	j = 0;
	while (av[++j])
		ft_unsetenv(env, av[j]);
	return (EXIT_SUCCESS);
}
