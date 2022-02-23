/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/22 09:36:55 by thi-phng         ###   ########.fr       */
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


// DOUBLE QUOTES principales //
int	ft_d2_quotes(char *str, int *i, char *line, t_cmd *one_cmd)
{
	if (ft_check_2rd_quote(&line[*i], '"'))
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
