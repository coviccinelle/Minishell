/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/14 16:58:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../minishell.h"


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


// int	ft_check_2rd_quote_2(char *line, int c)
// {
// 	int		i;
// 	//int		q;

// 	i = 0;
// 	//q = 0;
// 	while (line[i])
// 	{
// 		if (line[i + 1] && line[i + 1] == c)
// 		{
// 		//	q++;
// 			i++;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	// if (q % 2 == 0)
// 	// 	return (1);
// 	// else if (q % 2 != 0)
// 	// 	return (0);
	
// 	//printf("No 2rd quote detected !!!\n\n\n");// \np final is = %d\n", q);
// 	return (0);
// }


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

// //euhhhhh
// char	*ft_add_2rd_quote(t_mini *one_cmd, int *i, char *line, char *str)
// {
// 	//(void)one_cmd;
	
// 	if (!ft_check_2rd_quote(&line[*i], '"'))
// 	{
// 		printf("ERROR: Double quotes are not safely closed\n");
// 		one_cmd->stop = 1; //->g_n_exit = ???;
// 		return (0);
// 	}
// 	printf("ok check quote\n\n");
// 	(*i)++;
// 	while (line[*i] && line[*i] != '"')
// 	{
// 		str = ft_add_line_after(str, line[(*i)]);
// 	//	printf("3.0 line_after = %s\n", line_after);
// 		(*i)++;
// 	}
// 	printf("3. line_after in 3rd layer is: _%s_\n", str);
// 	if (str)
// 		ft_avs(one_cmd, str);
// 	return (str);
// }


// DOUBLE QUOTES principales //
int	ft_d2_quotes(char *str, int *i, char *line, t_mini *one_cmd)
{
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
		str = ft_add_line_after(str, line[(*i)]);
	//	printf("3.0 line_after = %s\n", line_after);
		(*i)++;
	}
	printf("3. line_after in 3rd layer is: _%s_\n", str);
	if (str)
	{
		printf("Inside str exist, adding in ft_avs\n");
		ft_avs(one_cmd, str);
		return (1);
	}
	free(str);
	return (0);
}


// //ft _   DOUBLE  _quotes
// char	*ft_d2_quotes_2(char *str, int *i, char *line, t_mini *one_cmd)
// {
// 	// useless
// 	// if (line_after)
// 	// {
// 	// 	printf("2. line_after in 2nd layer is %s\n", line_after);
// 	// 	ft_avs(one_cmd, line_after);
// 	// 	line_after = NULL;
// 	// }
// 	// // done useless
// 	str = ft_add_2rd_quote(one_cmd, i, line, str);
// 	if (str == NULL)
// 		return (NULL);
// 	return (str);
// }


//add_2rd single quote
//int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *str)
int	ft_single_quote(char *str, int *i, char *line, t_mini *one_cmd)
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
