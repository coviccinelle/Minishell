
#include "../../minishell.h"

int	is_redir_error(char *str)
{
	int	i;

	i = 1;
	if (str[i] == str[i - 1])
		i++;
	i += skip_blank_2(&str[i]);
	if (!str[i] || is_redir(str[i]) || str[i] == '|')
		return (1);
	return (0);
}
// done redir error

int	syntax_error(t_cmd *mini)
{
	(void)mini;
	printf("ERROR : Syntax error\n");
	return (0);
}

int	ft_syntax_error(t_cmd *mini)
{
	int	i;
	char	*str;

	i = 0;
	str = mini->line;
	while (str[i])
	{
		if (is_redir(str[i]) && is_redir_error(&str[i]))
			return (syntax_error(mini/*, REDIR*/));
		else if (str[i] == '|' && is_pipe_error(&str[i]))
			return (syntax_error(mini/*, PIPE*/));
		i++;
	}
	return (SUCCESS);
}
