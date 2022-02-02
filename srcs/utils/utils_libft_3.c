#include "../../minishell.h"


void	ft_memdel(char	**s)
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

void	free_tab(char ***line)
{
	int	i;
	
	i = 0;
	while ((*line)[i])
	{
		free((*line)[i]);
		i++;
	}
	free((*line)[i]);
	free(*line);
}

