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



 
int	ft_strchr_lst(t_export *export_lst, char *export_name)
{
	t_export *tmp;

	tmp = export_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, export_name) == 0)
			return (1); // et enregistrer dans une struct ce que j’ai trouvé lst→found**
		tmp = tmp->next;
	}
	return (0);
}


void	delete_export(t_export **export_lst, char *export_name)
{
	t_export *tmp;

	tmp = *export_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, export_name) == 0)
				break ;
		tmp = tmp->next;
	}
/*
	next = tmp->next->next; // Node temp->next is the node to be deleted
	free(tmp->next);
	tmp->next = next;
*/
	tmp->next = tmp->next->next;
	free(tmp->next);
}


int exec_unset(int ac, char **av, t_export **export_lst)
{
	t_export	*lst_export;

	lst_export = *export_lst;
	int exit_status;
	int j;
	exit_status = EXIT_SUCCESS; //success si tout est ok. fail si tout a fail mais a revoir si pas tous les args ont fail
	if (ac < 2)
	{
		ft_puterror_fd("unset: not enough arguments", NULL, NULL);
		return (EXIT_FAILURE);
	}
	j = 1; // pour sauter cmd unset. après à voir en fonction de notre parsing
	while(av[j])
	{
		if(!is_valid_var_name(av[j]))
		{
			ft_puterror_fd("unset: ", av[j], ": invalid parameter name");
			exit_status = EXIT_FAILURE; /// valeur de ret a checker car bizarre il fait le reste malgré tout donc demi -csuccès
		}
		if (ft_strchr_lst(lst_export, av[j]) == 0) 
			delete_export(&lst_export, av[j]); 
		j++;
	}
	return (exit_status); //"The return status is zero unless a name is readonly". moi j'entends que si un seul fail tout fail niveau ret' donc normalement mon truc est bon (cf page unset du BASH)
}

//utils ft_strchr_lst; 
// sera la même normalement que utilisé dans 4/ pour les expansions $
// faire la même mais version strcmp (tiré de mon pushswap)**



//https://www.geeksforgeeks.org/delete-a-linked-list-node-at-a-given-position/ 




int main(int ac, char **av)
{
	(void)ac;
	t_env *env;	

	env = NULL;
	exec_export(ac, av, &env);
	printf("Print = $$$$$$$$\n");
	printexport(env->export);
	
	return (0);
}

