#include "../minishell.h"

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

