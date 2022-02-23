/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:25:42 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/22 22:12:30 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	env_realloc_and_append_envvar(char ***env, char *envvar)
{
	int		j;
	char	**new_env;
	int		new_size;

	j = 0;
	new_size = nb_tabs(*env) + 2;
	new_env = (char **)malloc(sizeof(char *) * new_size);
	if (!new_env)
		return (-1);
	while ((*env)[j] && j < nb_tabs(*env))
	{
		new_env[j] = ft_strndup((*env)[j], ft_strlen((*env)[j]));
		j++;
	}
	new_env[j] = ft_strndup(envvar, ft_strlen(envvar));
	new_env[j + 1] = NULL;
	free_tab(env);
	*env = new_env;
	return (0);
}

char	*find_in_env(char **env, char *name, int *pos)
{
	int	j;
	int	name_len;

	name_len = ft_strlen(name);
	j = -1;
	printf("JE PASSE DANS FIND ENV\n\n");
	if (name == NULL || env == NULL)
	{
		printf("dans find env, name == NULL or !env\n\n");
		return (NULL);
	}
	while (env[++j] && j < nb_tabs(env))
	{
		if (ft_strncmp(name, env[j], name_len) == 0)
		{
			*pos = j;
			printf("dans find envs, show it\n\n");
			return (cpy_trim(env[j], '=', '\0'));
		}
	}
	return (NULL);
}

char	*ft_getenv(char **env, char *name)
{
	int	pos;

	pos = 0;
	return (find_in_env(env, name, &pos));
}

int	ft_setenv(char ***env, char *av, char *name, char *value)
{
	int	pos_name;
	(void)value; //pourquoi jai mis void value deja?

	if (find_in_env(*env, name, &pos_name) != NULL)
		ft_unsetenv(env, name);
	env_realloc_and_append_envvar(env, av);
	return (0);
}

int get_into_export_lst(char ***env, char **av, char **name, char **data)
{
	int j;
	
	j = 1;
	while (j < nb_tabs(av))
	{
		if (name[j] != NULL)
		{
			printf("added %s=%s. name = |%s|, value = |%s|\n", name[j], data[j], name[j], data[j]);
			ft_setenv(env, av[j], name[j], data[j]);
		}
		j++;
	}
	return (0);
}

void	init_tab(char **av, char ***s)
{
	//*s = NULL;
	*s = malloc(sizeof(char **) * (nb_tabs(av)));

}

int exec_export(int ac, char **av, char ***env) // liste a faire dans point 4/expansions
{
	char **name; // de la taille de **av
	char **data; //idem 
	int j;
	int exit_value = EXIT_SUCCESS;
	
	j = 0;
	//init_tab(av, &name);
//	init_tab(av, &data);

	data = malloc(sizeof(char **) * (nb_tabs(av))); //essayer data[nb_tabs[]]
	name = malloc(sizeof(char **) * (nb_tabs(av)));
	if (ac == 1)
		return (ft_alphabetical_order_tab(*env));
	while (av[++j])
	{
		name[j] = cpy_trim(av[j], av[j][0], '=');
		if (!is_valid_var_name(name[j]))
		{
			exit_value = ft_puterror_fd("minishell: export :'", av[j], "': not a valid identifier");
			name[j] = NULL;
		}
		data[j] = cpy_trim(av[j], '=', '\0');
	}
	get_into_export_lst(env, av, name, data);
	j = 1;
	free(data);
	free(name);
//	free_tab(&name); //  leaks dans mes init tabs que je free data et name ou pas... a comprendre
//	free_tab(&data); // idem
	return (exit_value);
}

int	ft_unsetenv(char ***env,char *name)
{
	int pos_name;
	int	j;
	char	*found;

	found = find_in_env(*env, name, &pos_name);
	if (!found)
		return(0);
	j = pos_name;
	while((*env)[j] && j < nb_tabs(*env))
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
	(void)ac;
	int j;

	j = 0;
	while (av[++j])
		ft_unsetenv(env, av[j]);
	return (EXIT_SUCCESS);
}
