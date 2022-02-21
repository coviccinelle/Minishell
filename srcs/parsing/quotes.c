/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/21 11:19:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	check_quote(char *str, int i)
{
	int	quote;

	if (str[i] != '\'' && str[i] != '\"')
		return (0);
	quote = str[i++];
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

int is_quote_err(char *str)
{
    int i;
    int k;
	int j;

    i = 0;
    while (str[i])
    {
        k = address_1st_quote(&str[i]);
        if (k == -1)
            return (0); //not found any quote
        j = check_quote(&str[i], k);
		if (j != 0)
			i += j;
		else if (j == 0)
			return (42);
	   	i++;
    }
    return (0);
}
// done check quote

int	ft_check_2rd_quote(char *str, int a)
{
	char	c;
	int		i;
	int		p;

	i = 0;
	c = a;
	p = 0;
	while (str[i])
	{
		if (i != 0 && str[i + 1] && str[i + 1] == c)
		{
			p++;
			break ;
		}
		if (str[i] == c)
			p++;
		i++;
	}
	if (p % 2)
		return (0);
	else
		return (1);
}

void	ft_pass_squote(char *str, int *i)
{
	if (str[(*i) + 1] == 34)
		(*i)++;
	else if (str[(*i) + 1] == ' ')
	{
		(*i)++;
		while (str[(*i)] == ' ')
			(*i)++;
	}
	else if (str[(*i)] == 39 && str[(*i) + 1] && str[(*i) + 1] != ' ')
		(*i)++;
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


int		is_dollar(char *str, int *i)
{
	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ')
		return (1);
	return (0);
}

//replacing dollar_sign by 
char	*ft_dollar_sign(char *str)
{
	// int i;
	// char	*line_2;

	// i = 0;
	// line_2 = NULL;
	// while (str[i])
	// {
	// 	line_2 = 
	// }
	printf("dollar_sign later, return a char *, str = %s\n", str);	
	return (NULL);
}

// DOUBLE QUOTES principales //
int	ft_d2_quotes(char *str, int *i, char *line, t_cmd *one_cmd)
{
	char	*line_2;
	
	line_2 = NULL;
	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("ERROR: Double quotes are not safely closed\n");
	//	one_cmd->stop = 1; //->g_n_exit = ???;
		return (0);
	}
	printf("ok check quote\n\n");
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		if (find_me('$', &line[*i]))
			line_2 = ft_dollar_sign(&line[*i]);
		else
			line_2 = str;
	//	if (line[*i] == '$' && line[*i + 1] && line[*i + 1] != ' ')
		line_2 = ft_add_line_after(line_2, line[(*i)]);
		(*i)++;
	}
	printf("3. line_after in 3rd layer is: _%s_\n", line_2);
	if (line_2)
	{
		printf("Inside str exist, adding in ft_avs\n");
		ft_avs(one_cmd, line_2);
		return (1);
	}
	free(str);
	return (0);
}

//int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *str)
int	ft_single_quote(char *str, int *i, char *line, t_cmd *one_cmd)
{
	int		start;

	start = (*i);
	(*i)++;
	if (!ft_check_2rd_quote(&line[start], '\''))
	{
		free(str);
		printf("Error: Second single quote not found\n\n");
		//g_n_exit = ??
		return (0);
	}
	while (line[(*i)] && line[(*i)] != '\'')
	{
		str = ft_add_line_after(str, line[(*i)]);
		(*i)++;
	}
	if (str)
		ft_avs(one_cmd, str);
	return (1);
}
