#include "../../minishell.h"

//revoir en fonction de thao
void		expansions(char **av)
{
	int j;

	j = -1;
	while (av[++j])
	{
		if (av[j][0]  == '$' && av[j][1]  == '?')
			get_exit_status(); // comment vu que pas possible var globale?? Ret de fonction a mettre dans notre liste chainee “mini”?
		else if (av[j][0]  == '$')
			ft_getenv(av[j]); // rechecker nom final que je lui ai donne et tester le tout
		else if (av[j][0]  == '~')
			ft_getenv("HOME");
	}
}

// + a remplacer dans la liste chainee au bon endroit of course. a 

  

