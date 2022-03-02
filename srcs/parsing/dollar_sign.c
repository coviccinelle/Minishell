
#include "../../minishell.h"

char	*dolar_name(char *str, int *i, char *line_after, t_cmd *cmd)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	(*i)++;
	while (str[*i] && str[*i] != ' ')
	{
		line_after = ft_add_line_after(line_after, str[*i]);
		(*i)++;
	}
	return (line_after);
}

char	*dolar_2(char *str, int *i, char *line_after, char **envp)
{
	line_after = ft_getenv(envp, line_after);
	if (str[*i])
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	return (line_after);
}
