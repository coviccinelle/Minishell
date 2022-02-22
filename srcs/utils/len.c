
#include "../../minishell.h"


int	ft_len_cmd(char **str)
{
	int i;

	i = 0;
	while(*str[i])
		i++;
	return (i);
}
