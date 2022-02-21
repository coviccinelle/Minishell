

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_file *file)
{
    if (line[*i] == '<' && line[(*i) + 1] == '<')
        file->type = heredoc;
    if (line[*i] == '>' && line[(*i) + 1] == '>')
        file->type = right_2;
    if (line[*i] == '<' && line[(*i) + 1] != '<')
        file->type = left;
    if (line[*i] == '>' && line[(*i) + 1] != '>')
        file->type = right;
}

int	check_redir(char *str, int i)
{
	int	p;
	int	j;

	p = 0;
	j = i;
	while (str[i] == '>' || str[i] == '<')
	{
		p++;
		i++;
	}
	if (p == 1 || p == 2)
	{
		if (p == 1)
			return (1);
		else if (p == 2 && str[j] == str[j + 1])
			return (1);
	}
	return (0);
}
