#include "minishell.h"

//a tester
char *handle_expansions(char *av)
{
	char *av_bis;

	av_bis = NULL; //plutot is in export lst que valid_var_name non au vu tests en haut? saute les chiffres si av[j][1]?
	if (av[j][0] == ‘$’ && (is_valid_var_name(&av[j][1])) // si signe dollar c'est un export. oblige detre un valid var name??
		av_bis = get_export(&env->export_lst, &av[j][1]);
	else //si av[j][1] est un chiffre ft_strcpy(&av[j][1]) plutot
		av_bis = ft_strcpy(av[j]); // si pas de signe dollar
	return (av_bis);
}

char 	*get_export(t_export *export_lst, char *export_name)
{
	t_export *tmp;
	if (!export_lst)
		return (NULL);

	tmp = *export_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, export_name) == 0)
			return (tmp->data); // si trouvé
		tmp = tmp->next;
	}
	return (NULL); // si pas trouvé renvoie chaine vide (sans le signe $)
}
