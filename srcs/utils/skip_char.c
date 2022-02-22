
#include "../../minishell.h"


int	skip_diff(char *str)
{
	int	i;
	int	quote_type;

	i = 1;
	quote_type = str[i++];
	while (str[i] && str[i] != quote_type)
		i++;
	return (i);
}

int	is_blank(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	skip_blank(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	return (i);
}


int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
