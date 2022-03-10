/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:16:58 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/10 11:03:29 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_into_export_lst(char ***env, char **av, char **name, char **data)
{
	int	j;

	j = 0;
	while (av && av[j] && av[j + 1])
	{
		if (name[j])
			ft_setenv(env, av[j + 1], name[j], data[j]);
		j++;
	}
	return (0);
}

void	free_all(char ***name, char ***data, char **av)
{
	int	j;

	j = 0;
	while (av[j + 1])
	{
		if (*name[j])
			free(*name[j]);
		if (*data[j])
			free(*data[j]);
		j++;
	}
	free(*name);
	free(*data);
}

char	*l(char *line)
{
	int		i;
	int		c;
	char	*s;

	i = -1;
	while (line && line[++i])
	{
		if (line[i] == '=')
		{
			i++;
			c = 0;
			while (line[i + c])
				c++;
			s = malloc(sizeof(char) * (c + 1));
			c = -1;
			while (line[i + (++c)])
				s[c] = line[i + c];
			s[c] = '\0';
			return (s);
		}
	}
	return (NULL);
}

void	init(int *j, int *c, int *exit_value)
{
	*c = 1;
	*exit_value = EXIT_SUCCESS;
	*j = 0;
}

void	init_1(char ***data, char ***name, char **av)
{
	*data = malloc(sizeof(char *) * (nb_tabs(av) + 1));
	*name = malloc(sizeof(char *) * (nb_tabs(av) + 1));
}

void	unvalid_name_case(int *exit_value, \
			char **name_j, char **data_j, char *av_j)
{
	*exit_value = ft_puterror_fd("minishell: export :'", \
			av_j, "': not a valid identifier");
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

	init(&j, &c, &exit_value);
	init_1(&data, &name, av);
	if (ac == 1)
		return (ft_alphabetical_order_tab(*env));
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
	get_into_export_lst(env, av, name, data);
	free_all(&name, &data, av);
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
