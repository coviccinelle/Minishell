/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:16:58 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/10 18:31:36 by thi-phng         ###   ########.fr       */
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
	free_tab_3(name, nb_tabs(name));
	free_tab_3(data, nb_tabs(data));
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
