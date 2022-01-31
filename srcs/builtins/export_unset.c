#include "../../minishell.h"


//char *ft_strstr(char *str, char *to_find);
void				ft_bzero(void *b, size_t n);
void	*ft_memalloc(size_t size);
void	test_print(char **envp);
void	free_tab(char ***line);
void	free_tabs(char **tabs);
void ft_putchar(int c);
void ft_putstr(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*cpy_trim(char *s, char from, char to);
int ft_strncmp(char *s1, char *s2, unsigned int n);
//char *ft_strcat(char *dest, char *src);
int		nb_tabs(char **s);
char	*ft_strdup(char *src);
char	*ft_strcpy(char *dst, char *src);
int	ft_alphabetical_order_tab(char **env);
void	print_tab(char **env);
char	**ft_copy_tab(char **env);
int	ft_unsetenv(char ***env,char *name);
void	print_export(char **tab);


int		env_realloc_and_append_envvar(char ***env, char *envvar)
{
	int	j;
	char	**new_env;
	int	new_size;

	j = -1;
	new_size = nb_tabs(*env) + 1;
	new_env = (char **)malloc(sizeof(char *) * new_size + 1);
	if (!new_env)
		return (-1); // voir quelle valeur dans errno
	while ((*env)[++j])
		new_env[j] = ft_strdup((*env)[j]);
	new_env[j] = ft_strdup(envvar);
	new_env[j + 1] = NULL;
	*env = new_env;
	return (EXIT_SUCCESS);
}


char	*find_in_env(char **env, char *name, int *pos) //prend tout bonjour=hello et non pas juste le name
{
	int	j;
	int	name_len;

	name_len = ft_strlen(name);
	j = -1;
	printf("JE PASSE DANS FIND ENV\n\n");
	if (name == NULL || env == NULL)
		return (NULL);
	while (env[++j])
	{
		if (ft_strncmp(name, env[j], name_len) == 0 && env[j][name_len] ==  '=')
		{
			*pos = j;
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
	
	printf("JE PASSE DANS SET ENV\n\n");
	if (find_in_env(*env, name, &pos_name) != NULL)
		ft_unsetenv(env, name);
	env_realloc_and_append_envvar(env, av);
	return (0);
}

//dans l'ordre alphabétique mon add_node...
int get_into_export_lst(char ***env, char **av, char **name, char **data)
{
	int j;
	
	j = 1;
	while (name[j])
	{
		if (name[j] != NULL)  // ok du moment que name ok, si data est null  va justeassocier une chaine vide a name
		{
			printf("added %s=%s. name = |%s|, value = |%s|\n", name[j], data[j], name[j], data[j]);
			ft_setenv(env, av[j], name[j], data[j]);
		}
		j++;
	}
//necessaire de checker si le name est deja dans lea lst? si oui dans ce cas defonction remplace (supprime et cpy nouvelle valeure)
	return (EXIT_SUCCESS);
}

void	init_tab(char **av, char ***s)
{
	*s = NULL;
	*s = malloc(sizeof(char **) * nb_tabs(av) + 1);
	//tout set a null, les tabs comme les strings
}

int exec_export(int ac, char **av, char ***env) // liste a faire dans point 4/expansions
{
	char **name; // de la taille de **av
	char **data; //idem 
	int j;
	
	j = 0;
	init_tab(av, &name);
	init_tab(av, &data);
	if (ac == 1) // if just exportprint env ou liste export
		return (ft_alphabetical_order_tab(*env));
	while (av[++j])
	{
		name[j] = cpy_trim(av[j], av[j][0], '=');
		if (!is_valid_var_name(name[j]))
		{
			ft_puterror_fd("minishell: export ", name[j], ": not a valid identifier");
			name[j] = NULL;
		}
		data[j] = cpy_trim(av[j], '=', '\0');
	}
	get_into_export_lst(env, av, name, data);
	free_tab(&name); // a free en mode gnl aussi !! free_tab
	free_tab(&data); // idem
	return (EXIT_SUCCESS);
}


int	ft_unsetenv(char ***env,char *name)
{
	int pos_name;
	int	j;

	//find_in_env(*env, name, &pos_name); //a voir si peux supp cette ligne
	if (!find_in_env(*env, name, &pos_name)) //comme ca exit si nexiste pas dans environ?a checker
		return(0); // ret 0 car pas un echec en soi?
	j = pos_name;
	while((*env)[j])
	{
		ft_memdel(&(*env)[j]);
		(*env)[j] = ft_strdup((*env)[j + 1]);
		ft_memdel(&(*env)[j + 1]);
		j++;
	}
  return (0);
}

/*
int	cmd_unset(int ac, char **av, char ***env)
{
	int j;

	j = 0; // car a partir de av[1] donc apres unset
	while (av[++j]) // a tester. ai ajouté if pas found dans l'env dans ft_unsetenv. si ne marche pas, mettre ici
		ft_unsetenv(&env, av[j]);
	return (0);
}
*/

int		main(int ac, char **av, char **envp)
{

	(void)ac;

	char **env;

	env = ft_copy_tab(envp);
	printf("******************************************ENV AVANT***************************8\n");
	print_tab(env);
	printf("*******************************************APRES EXPORT***************************8\n");
	exec_export(ac, av, &env);
	print_tab(env);
	printf("*******************************************APRES UNSET**************************\n");
	ft_unsetenv(&env, "bonjourrr"); // encore a tester apres parsing Thao : cmd_unset pour que arg1 arg2 etc soient tous unset.
	print_tab(env);

	printf("*******************************************EXPORT ALPHABETIQUE**************************\n");
	print_export(env);
	return (0);
}
