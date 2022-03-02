
#include "../../minishell.h"

// char	*dollar_sign(int ac, char **av, char **env)
// {
// 	int j;
// 	char	*s;

// 	s = NULL;
// 	j = -1;
// 	while (av[++j])
// 	{
// 		if (av[j][0]  == '$' && av[j][1]  == '?')
// 			get_exit_status(); // comment vu que pas possible var globale?? Ret de fonction a mettre dans notre liste chainee “mini”?
// 		else if (av[j][0]  == '$' && av[j][1] != NULL)
// 			s = ft_getenv(env, av[j]); // rechecker nom final que je lui ai donne et tester le tout
// 		else if (!ft_strcmp(av[j], "~"))
// 			s = ft_getenv(env, "HOME"); // a free
// 	}
// 	return(s);
// }



int	is_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$' && is_alpha(str[i + 1]))
		return (1);
	else
		return (0);
}


// *** // Dollar sign : go search the value in
// char	*dollar_sign_1(char *str, int *i, char *line_after)
// {
// 	char	*name;

// 	name = NULL;
	
// 	//if (str[*i] == '$' && is_alpha[*i + 1])
// 	while (str[*i])
// 	{
// 		(*i)++;
// 		while (str[*i] && str[*i] != ' ')
// 		name = ft_add_line_after(name, str[*i]);

// 	}

// }
