/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:16:58 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/11 17:32:37 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	unvalid_name_case(int *exit_value, \
			char **name_j, char **data_j, char *av_j)
{
	(void)av_j;
	*exit_value = ft_puterror_fd("minishell: export :'", \
			name_j[0], "': not a valid identifier");
	if (*name_j)
		free(*name_j);
	*name_j = NULL;
	*data_j = NULL;
}

int	exec_export(int ac, char **av, char ***env)
{
	char			**name;
	char			**data;
	int				j;
	int				c;
	int				exit_value;

	if (ac == 1)
		return (ft_alphabetical_order_tab(*env));
	init(&j, &c, &exit_value);
	init_1(&data, &name, av);
	while (av[j + c])
	{
		name[j] = cpy_trim(av[j + c], av[j + c][0], '=');
		if (!is_valid_var_name(name[j]))
			unvalid_name_case(&exit_value, &name[j], &data[j], av[j]);
		else
			data[j] = l(av[j + c]);
		j++;
	}
	name[j] = NULL;
	data[j] = NULL;
	get_into_export_lst(env, av, name, data);
	return (exit_value);
}

int	ft_unsetenv(char ***env, char *name)
{
	int			pos_name;
	int			j;
	char		*found;

	found = find_in_env(*env, name, &pos_name);
	if (ft_strcmp(found, "") == 0)
	{	
		if (found)
			free(found);
		return (0);
	}
	if (found)
		free(found);
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
