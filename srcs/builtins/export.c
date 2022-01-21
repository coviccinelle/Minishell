#include "../../minishell.h"

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

#include <string.h>
//dans l'ordre alphabétique mon add_node...
int get_into_export_lst(char **av, char **name, char **data, t_mini **mini)
{
//sous forme de tableau car rien n'est pris en compte dans bash si une seule erreur dans un seul arg donc doit m'assurer que totut est ok avant envoi àl st export
	*mini = malloc(40000); //quelle size malloc? en dehors de pref. a voir portabilite si je mets dans le main principal
	t_mini *tmp;
	int j;
	
	tmp = *mini;
	j = 1;
	while (name[j])
	{
	//	add_to_export_lst(&tmp->export, NULL, name[j], data[j]); // à export list. nom étant avant = et data étant après = et jusqu'à nouveau av[j].
		if (name[j])
		{
			add_to_export_lst(&tmp->export, NULL, name[j], data[j]);
			//add_to_env(&tmp->env, NULL, name[j], data[j]);
		}
		j++;
	}
//necessaire de checker si le name est deja dans lea lst? si oui dans ce cas defonction remplace (supprime et cpy nouvelle valeure)
	return (EXIT_SUCCESS);
}

int exec_export(int ac, char **av, t_mini **mini) // liste a faire dans point 4/expansions
{
	char **name; // de la taille de **av
	char **data; //idem 
	int j;

	j = 0;
	name = NULL;
	data = NULL;
	name = malloc(sizeof(char *) * 10000); // strlen de av je me dis ca fait plus serieux
	data = malloc(sizeof(char *) * 10000); // same 
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
	get_into_export_lst(av, name, data, mini);
	free_tab(&name); // a free en mode gnl aussi !! free_tab
	free_tab(&data); // idem
	return (EXIT_SUCCESS);
}


/*
void	printstack(t_env *env)
{
	while (env)
	{
		printf("%s =  ", env->export->name);
		printf("%s\n", env->export->value);
		env = env->next;
	}	
}
*/

void	printstack(t_mini *mini)
{
	while (mini)
	{
		printf("%s =  ", mini->export->name);
		printf("%s\n", mini->export->value);
		mini = mini->next;
	}	
}

#include <string.h>


t_export *new_export(char *av, char *export_name, char *export_data)
{
	t_export *export; // a voir t_env out t_export sachant que t_export est dans t_env

	export = (t_export*)malloc(sizeof(t_export));

	if (!export)
	{
		ft_puterror_fd("overflow", NULL, NULL);
    	//	ft_free_lst(&lst->export);
		return(0);
	}
	export->name = export_name;
	export->value = export_data;
	export->envj = av;
	export->next = NULL;
	return (export);
}


void	printexport(t_export *export)
{
	while (export)
	{
		printf("declare -x ");
		//if (export->name != NULL && export->value == NULL && export->envj == NULL) // export bonjour= print bien bonjour=""
		//	printf("%s=\"\"\n", export->name);
		if (export->name != NULL /*&& export->value != NULL*/)
			printf("%s=\"%s\"\n", export->name, export->value);
	//	else if (export->name != NULL && export->value == NULL && export->envj == NULL) // a regler, export bonjour devrait print bonjour
	//		printf("%s\n", export->name);
		else if (export->envj != NULL)
			printf("%s\n", export->envj);
		export = export->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	get_right_index(t_export **head, t_export *newnode)
{
	t_export	*tmp;
	int	pos;

	tmp = (*head)->next;
	pos = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, newnode->name) < 0)
			pos++;
		tmp = tmp->next;
	}
	return (pos);
}

void add_to_export_lst(t_export **export_lst, char *envj, char *export_name, char *export_data)
{
	t_export *newnode;
	t_export *tmp;
	tmp = *export_lst;
	newnode = new_export(envj, export_name, export_data);
	if ((!*export_lst) || ft_strcmp((*export_lst)->name, newnode->name) > 0)
	{
		newnode->next = *export_lst;
		*export_lst = newnode;
	}
	else
	{
		tmp = *export_lst;
		while (tmp->next != NULL && (ft_strcmp(tmp->next->name, newnode->name) < 0))
		{
			tmp = tmp->next;
        	}
		newnode->next = tmp->next;
		tmp->next = newnode;
	}
}

/*
int main(int ac, char **av)
{
	(void)ac;
	t_mini *mini;	

	mini = NULL;
	exec_export(ac, av, &mini);
	printf("Print = $$$$$$$$\n");
	printexport(mini->export);
	
	return (0);
}
*/
