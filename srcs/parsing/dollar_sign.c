
#include "../../minishell.h"

char	*expansions(int ac, char **av, char **env)
{
	int j;
	char	*s;

	s = NULL;
	j = -1;
	while (av[++j])
	{
		if (av[j][0]  == '$' && av[j][1]  == '?')
			get_exit_status(); // comment vu que pas possible var globale?? Ret de fonction a mettre dans notre liste chainee “mini”?
		else if (av[j][0]  == '$' && av[j][1] != NULL)
			s = ft_getenv(env, av[j]); // rechecker nom final que je lui ai donne et tester le tout
		else if (!ft_strcmp(av[j], "~"))
			s = ft_getenv(env, "HOME"); // a free
	}
	return(s);
}