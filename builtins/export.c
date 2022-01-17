#include "../minishell.h"

int failure_cases_export_1(char *name)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	//printf("checking name = %s\n", name);
	if (is_digit(name[0]))
		ft_puterror_fd("export: not an identifier: ", name, NULL);
	else if (!is_valid_var_name(name))
		ft_puterror_fd("export: not valid in this context: ", name, NULL);
	else
		exit_status = EXIT_SUCCESS;
	return (exit_status);
}

#include <string.h>

int failure_cases_export_2(char *av, char *data, char *name)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
//	printf("checking name = %s // data = %s\n", name, data);
	if (strcmp(av, "=") == 0) // a modif en ft_strcmp !!
		ft_puterror_fd("minishell: bad assignment", NULL, NULL);
	else if (av[0] == '=' && data != NULL) //surement a enlever car gere dans le main normalement
		ft_puterror_fd("minishell: ", name, " not found");
	else
		exit_status = EXIT_SUCCESS;
	return (exit_status);
}

//dans l'ordre alphabétique mon add_node...
int get_into_export_lst(char **name, char **data, t_env **env)
{
//sous forme de tableau car rien n'est pris en compte dans bash si une seule erreur dans un seul arg donc doit m'assurer que totut est ok avant envoi àl st export
	t_env *tmp;
//	t_export *export;

	tmp = *env;
//	export = tmp->export;
	int j;

	j = 1;
	while (name[j])
	{
		if (name[j] != NULL)  // ok du moment que name ok, si data est null  va justeassocier une chaine vide a name
			printf("added %s=%s\n", name[j], data[j]);
			add_to_export_lst(&tmp->export, name[j], data[j]); // à export list. nom étant avant = et data étant après = et jusqu'à nouveau av[j]. 
		j++;
	}
//necessaire de checker si le name est deja dans lea lst? si oui dans ce cas defonction remplace (supprime et cpy nouvelle valeure)
	return (EXIT_SUCCESS);
}

int exec_export(int ac, char **av, t_env **env) // liste a faire dans point 4/expansions
{
	char **name; // de la taille de **av
	char **data; //idem 
	int j;

	j = 0;
	name = NULL;
	data = NULL;
	name = malloc(sizeof(char *) * 1000);
	data = malloc(sizeof(char *) * 1000);
/*	if (ac == 1) // if just exportprint env ou liste export
	{
		printstack(env) //env avec list export par ordre alphabetique ?
		return (EXIT_SUCCESS);
	} */
	while (av[++j])
	{
		name[j] = cpy_trim(av[j], av[j][0], '=');
		if (failure_cases_export_1(name[j]) == EXIT_FAILURE)
			name[j] = NULL;
		data[j] = cpy_trim(av[j], '=', '\0'); // renvoie "" si rien!! 
		if (failure_cases_export_2(av[j], name[j],data[j]) == EXIT_FAILURE)
			name[j] = NULL; // si bug rajouter data[j] = NULL car tout fonctionnait avant
	}
	get_into_export_lst(name, data, env);
	free_tab(&name); // a free en mode gnl aussi !! free_tab
	free_tab(&data); // idem
	return (EXIT_SUCCESS);
}



void	printstack(t_env *env)
{
	while (env)
	{
		printf("%s =  ", env->export->name);
		printf("%s\n", env->export->value);
		env = env->next;
	}	
}

#include <string.h>


t_export *new_export(char *export_name, char *export_data)
{
	t_export *export; // a voir t_env out t_export sachant que t_export est dans t_env

	export = (t_export*)malloc(sizeof(*export));

	printf("je passe ici\n");
/*	if (!export)
	{
		ft_puterror_fd("overflow", NULL, NULL);
    		ft_free_lst(&lst->export);
		return(0);
	}
*/	export->name = export_name;
	export->value= export_data;
	export->next = NULL;
	return (export);
}

void add_to_export_lst(t_export **export_lst, char *export_name, char *export_data)
{
//in alphabetical order !
	t_export *newnode;
	t_export *tmp;
	int pos;

	pos = 0;
	tmp = *export_lst;
	printf("je passe ici\n");
	newnode = new_export(export_name, export_data);
	if (!*export_lst)
	{

		printf("je passe ici\n");
		*export_lst = newnode;
		return ;
	}
	while (tmp)
	{
		if (strcmp(tmp->name, export_name) > 0) // mettre ft_strcmp
			break ;
		tmp = tmp->next;
	}
	newnode->next = tmp; //point new node to current pos
	tmp = newnode; //now pointold node to newnode
}



//free all, du coup est ce que va prendre neen compte aussi t_data et dataenv ?etc ?
void	ft_free_lst(t_env **head)
{
	t_env	*lst;
	t_env	*next;

	lst = *head;
	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
	free(lst);
	*head = NULL;
}

int main(int ac, char **av)
{
	(void)ac;
	t_env *env;	

	env = NULL;
	exec_export(ac, av, &env);
	return (0);
}

