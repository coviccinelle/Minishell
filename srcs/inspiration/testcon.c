
#include <stdio.h>
#include <unistd.h>

// int	ft_strchr(const char *s, int c)
// {
// 	char		*str;

// 	//str = (char *)s + ft_strlen(s);
// 	while (*str != c)
// 	{
// 		if (str == s)
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }


// int		is_type(char *token, int type)
// {
// 	if (token && *token == type)
// 		return (1);
// 	else
// 		return (0);
// }

// int		is_types(char *token, char *types)
// {
// 	if (ft_strchr(types, ' ') && is_type(token, 0))
// 		return (1);
// 	else if (ft_strchr(types, 'X') && is_type(token, 1))
// 		return (1);
// 	return (0);
// }



int	ft_check_2rd_quote(char *argv, int c)
{
	int		i;
	int		q;

	i = 0;
	q = 0;
	while (argv[i])
	{
		if (argv[i + 1] && argv[i + 1] == c)
		{
			q++;
			return (1);
		}
		i++;
	}
	printf("No 2rd quote detected !!! \np final is = %d\n", q);
	return (0);
}

int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}


int	check_quote(char *str, int pos)
{
	int	quote_type;

	if (str[pos] != '\'' && str[pos] != '"')
		return (0);
	quote_type = str[pos++];
	while (str[pos])
	{
		if (str[pos] == quote_type)
			return (1);
		pos++;
	}
	return (0);
}

void	set_line(char *line, int *pos)
{
	while (line[*pos] && !is_redir(line[*pos]) && line[*pos] != '|')
	{
		if (line[*pos] == '$')
			//dollarsign
			printf("dollar sign! DO it please\n");
		else if (check_quote(line, *pos))
		{
			printf("check quote done, pos = %ls\n", pos);
			// quote_type = mini->line[*pos];
			// cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
			// while (mini->line[*pos] && mini->line[*pos] != quote_type)
			// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
			// if (mini->line[*pos] == quote_type)
			// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
		}
		else
			//cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
			printf("line[*pos] = %c\n", line[*pos]);
	}
}


int main(int ac, char **av)
{
	char *str = "hello coouou \"baby\" hihi";
	(void)av;

	if (ac != 1)
		printf("errrr: wrong number of argument\n");
	if (!check_quote(str, 1))
		printf("Hehe quote ok, all closed\n");
	
	// set_line(av[1], 0);
	// printf("done hihi\n");
    return (0);
}