#include "../../../minishell.h"

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
