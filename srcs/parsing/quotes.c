/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/09 16:44:05 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../minishell.h"


int	ft_check_2rd_quote(char *line, int c)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i + 1] == c)
			return (1);
		i++;
	}
	//printf("No 2rd quote detected !!!\n\n\n");// \np final is = %d\n", q);
	return (0);
}

char	*ft_add_2rd_quote(t_mini *one_cmd, int *i, char *line, char *line_after)
{
	(void)one_cmd;
	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("ERROR: Double quotes are not safely closed\n");
		one_cmd->stop = 1; //->g_n_exit = ???;
		return (0);
	}
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		line_after = ft_add_line_after(line_after, line[(*i)]);
		(*i)++;
	}
	return (line_after);
}

char	*ft_d2_quotes(char *line_after, int *i, char *line, t_mini *one_cmd)
{
	if (line_after)
	{
		ft_avs(one_cmd, line_after);
		line_after = NULL;
	}
	return (ft_add_2rd_quote(one_cmd, i, line, line_after));
}

int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *line_after)
{
	int		start;

	start = (*i);
	(*i)++;
	while (line[(*i)] && line[(*i)] != '\'')
	{
		line_after = ft_add_line_after(line_after, line[(*i)]);
		(*i)++;
	}
	if (!ft_check_2rd_quote(&line[start], '\''))
	{
		free(line_after);
		printf("Error: Second single quote not found\n\n"); //g_n_exit = ??
		return (0);
	}
	if (line_after)
		ft_avs(one_cmd, line_after);
	return (1);
}

int	ft_single_quote(char *line_after, int *i, char *line, t_mini *one_cmd)
{
	if (line_after)
	{
		ft_avs(one_cmd, line_after);
		line_after = NULL;
	}
	if (!ft_add_2rd_s_quote(one_cmd, i, line, line_after))
		return (0);
	return (1);
}
