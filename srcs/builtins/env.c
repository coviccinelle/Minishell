#include "../../minishell.h"

void	add_to_env(t_env **env, char *envj, char *name, char *value)
{
	t_env	*newnode;
	t_env	*tmp;

	tmp = *env;
	newnode = malloc(sizeof(env));
	//if (!newnode)
	//	ft_free_lst(env);
	newnode->envj = s;
	newnode->export_name = name;
	newnode->export_value = value;
	newnode->next = NULL;
	if (!(*env))
	{
		*env = newnode;
		return ;
	}
	while (tmp->next != 0)
		tmp = tmp->next;
	tmp->next = newnode;
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->envj);
		env = env->next;
	}	
}


int	main(int ac, char **av, char **envp)
{
	int	j;

	t_env	*env;

	env = NULL;
	j = -1;
	while (envp[++j])
	{
		//printf("%s\n", env[j]);
		add_to_stack(&env, envp[j], NULL, NULL); //ajoute dans lordre denv
		//add_to_export_lst(&export_lst, env[j]); //ajoute dans l'ordre ascii
	}

	print_env(env);
}
