
#include "../../minishell.h"

// flo
char	*add_char(t_mini *mini, char *str, int c)
{
	char	*new_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	new_str = malloc(len_str + 2);
	if (!new_str)
		exit_custom(mini, NULL, 500);
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	//free((void **)&str);
	return (new_str);
}


char	*ft_add_line_after_2(char *line, char buf)
{
	int		i;
	char	*new;

	if (line == NULL)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = buf;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(line);
	new = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf;
	new[++i] = '\0';
	free(line);
	return (new);
}