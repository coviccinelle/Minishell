
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	while ((src[i]) && i < dstsize - 1 && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

static char			**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void			ft_get_next_str(char **next_str, unsigned int *next_str_len,
					char c)
{
	unsigned int i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

char				**ft_split_3(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_strs + 1))))
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1))))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	//ft_free_tab(tab);
	return (tab);
}



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


// int	check_quote(char *str, int pos)
// {
// 	int	quote_type;

// 	if (str[pos] != '\'' && str[pos] != '"')
// 		return (0);
// 	quote_type = str[pos++];
// 	while (str[pos])
// 	{
// 		if (str[pos] == quote_type)
// 			return (1);
// 		pos++;
// 	}
// 	return (0);
// }

// void	set_line(char *line, int *pos)
// {
// 	while (line[*pos] && !is_redir(line[*pos]) && line[*pos] != '|')
// 	{
// 		if (line[*pos] == '$')
// 			//dollarsign
// 			printf("dollar sign! DO it please\n");
// 		else if (check_quote(line, *pos))
// 		{
// 			printf("check quote done, pos = %ls\n", pos);
// 			// quote_type = mini->line[*pos];
// 			// cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 			// while (mini->line[*pos] && mini->line[*pos] != quote_type)
// 			// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 			// if (mini->line[*pos] == quote_type)
// 			// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 		}
// 		else
// 			//cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 			printf("line[*pos] = %c\n", line[*pos]);
// 	}
// }



int	ft_len_cmd(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}


void print_tab(char **av)
{
	int j;

	j = 0;
	while(av[j])
	{
		printf("%s\n", av[j]);
		j++;
	}
}


// int	address_quote(char *str, int c)
// {
// 	int	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }


// int	check_quote(char *str, int i)
// {
// 	int	quote;

// 	printf("\nchar ici est : str[i] %c\n", str[i]); 
// 	if (str[i] != '\'' && str[i] != '\"')
// 		return (0);
// 	quote = str[i++];
// 	printf("place of i in quote = %d\n", i);
// 	printf("quote = %c\n", quote);
// 	while (str[i])
// 	{
// 		//printf("not quote is %c\n", str[i]);
// 		if (str[i] == quote)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }


// int main(int ac, char **av)
// {
// 	char *str = "hello coouou \"hihi\"babya hihi";
// 	(void)av;

// 	int 	a;

// 	// char **str_2;

// 	if (ac != 1)
// 		printf("errrr: wrong number of argument\n");
// 	//str_2 = ft_split_3(str, ' ');

// 	a = address_quote(str, '"');
// 	if (check_quote(str, a))
// 	{
// 		printf("\nadrress of the second quote is %d\n", check_quote(str, a));
// 		printf("check quote ok, found the second one\n");
// 	}
// 	else
// 		printf("ERROR: not found the second quote\n");

// 	// set_line(av[1], 0);
// 	// printf("done hihi\n");
//     return (0);
// }







int	address_quote(char *str, int c)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}


int	check_quote(char *str, int i)
{
	int	quote;

	//printf("\nchar ici est : str[i] %c\n", str[i]); 
	if (str[i] != '\'' && str[i] != '\"')
		return (0);
	quote = str[i++];
	//printf("place of i in quote = %d\n", i);
	//printf("quote = %c\n", quote);
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

int address_1st_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] == '\'') || (str[i] == '"'))
            return (i);
        i++;
    }
    return (-1);
}


// int	every_couple_quote(char *str, int i)
// {

// }

int is_quote_err(char *str)
{
    int i;
    int k;
	int j;

    i = 0;
    while (str[i])
    {
        k = address_1st_quote(&str[i]);
		printf("adrress of the first quote is %d\n", k);
		//printf("current i is %d\n", i);
        if (k == -1)
            return (42); //not found any quote
        j = check_quote(&str[i], k);
		if (j != 0)
			i += j;
		else if (j == 0)
			return (0);
	   	i++;
    }
    return (0);
}



int main(int ac, char **av)
{
	char *str = "hello' co\"ou'ou \"hihi\" ba b'ya hihi";
	(void)av;

	int 	a;

	// char **str_2;

	if (ac != 1)
		printf("errrr: wrong number of argument\n");
	//str_2 = ft_split_3(str, ' ');
	a = is_quote_err(str);
	printf("is_quote_err return %d\n", a);
    if (a != 0)
        printf("Quote ok -> no quote error\n");
    else if (a == 0)
        printf("Quote ERROR : no second quote found\n");



	// a = address_quote(str, '"');
	// if (check_quote(str, a))
	// {
	// 	printf("\nadrress of the second quote is %d\n", check_quote(str, a));
	// 	printf("check quote ok, found the second one\n");
	// }
	// else
	// 	printf("ERROR: not found the second quote\n");

	// set_line(av[1], 0);
	// printf("done hihi\n");
    return (0);
}