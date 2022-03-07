/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:16:58 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/07 15:40:50 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_into_export_lst(char ***env, char **av, char **name, char **data)
{
	int	j;
	
	j = 0;
	while(av && av[j] && av[j + 1])
	{
		if(name[j])
			ft_setenv(env, av[j + 1], name[j], data[j]);
		j++;
	}
	return(0);
}

void	free_all(char **name, char **data, char **av)
{
	int	j;

	j = 0;
	fprintf(stderr, "\n PRINT \n");
	while (av[j + 1])
	{
		fprintf(stderr, "\n name[j] %s \n", name[j]);
		if(name[j])
			free(name[j]);
		if(data[j])
		{
			fprintf(stderr, "\n data[j] %s \n", data[j]);
			free(data[j]);
		}
		j++;
	}
	free(name);
	free(data);
}


char*	l(char	*line)
{
	int	i;
	int	c;
	char	*s;

	i = -1;
	while(line && line[++i])
	{
		if(line[i] == '=')
		{
			i++;
			c = 0;
			while(line[i + c])
				c++;
			s = malloc(sizeof(char) * (c + 1));
			c = -1;
			while(line[i + (++c)])
				s[c] = line[i + c];
			s[c] = '\0';
			return(s);			
		}
	}
	return(NULL);
}

int	exec_export(int ac, char **av, char ***env)
{
	char			**name;
	char			**data;
	int				j;
	int				c;
	int				exit_value;

	c = 1;
	exit_value = EXIT_SUCCESS;
	j = 0;
	data = malloc(sizeof(char *) * (nb_tabs(av) + 1));
	name = malloc(sizeof(char *) * (nb_tabs(av) + 1));
	if (ac == 1)
		return (ft_alphabetical_order_tab(*env));
	while (av[j + c])
	{
		fprintf(stderr, "\n av[j + c] = %s\n", av[j + c]);
		name[j] = cpy_trim(av[j + c], av[j + c][0], '=');
		fprintf(stderr, "\n name = %s\n", name[j]);
		if (!is_valid_var_name(name[j]))
		{
			exit_value = ft_puterror_fd("minishell: export :'", \
					av[j], "': not a valid identifier");
			if(name[j])
				free(name[j]);
			name[j] = NULL;
			data[j] = NULL;
			j++;
		}
		else
		{
			//data[j] = cpy_trim(av[j + c], '=', '\0');
			data[j] = l(av[j + c]);
			if(data[j])
				fprintf(stderr, "\n data = %s\n", data[j]);
			else
				fprintf(stderr, "\n data = NULL \n");
			j++;
		}
	}
	name[j] = NULL;
	get_into_export_lst(env, av, name, data);
	free_all(name, data, av);
	return (exit_value);
}

int	ft_unsetenv(char ***env, char *name)
{
	int			pos_name;
	int			j;
	char		*found;

	found = find_in_env(*env, name, &pos_name);
	if (ft_strcmp(found, "") == 0)
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
