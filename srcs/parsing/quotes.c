/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/01 19:58:32 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_2rd_quote(char *str, char c)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] == c)
			p++;
		if (i != 0 && str[i + 1] && str[i + 1] == c)
		{
			p++;
			break ;
		}
		i++;
	}
	if (p % 2 != 0)
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


char	*ft_add_double_quote(t_cmd *cmd, int *i, char *line, char *line_after)
{
	//(void)cmd;
	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("\033[0;31m ERROR: Double quotes are not safely closed\033[0m\n");
		cmd->stop = 1;
		exit (0); // free tout stp
		//g_exit_value = 1;
		return (0);
	}
	(*i)++;
	printf("\033[0;32m ok Double quotes\033[0m\n");
	while (line[(*i)] != '"' && line[(*i)])
	{
		line_after = ft_add_line_after(line_after, line[(*i)]);
		(*i)++;
	}
	printf("line_after = %s\n", line_after);
	(*i)++; 
	return (line_after);
}

// // DOUBLE QUOTES principales //
char	*ft_d2_quotes(char *line_after, int *i, char *line, t_cmd *cmd)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	return (ft_add_double_quote(cmd, i, line, line_after));
}


char	*stock_single_quote(t_cmd *cmd, int *i, char *line, char *line_after)
{
	if (!ft_check_2rd_quote(&line[*i], '\''))
	{
		printf("\033[0;31m ERROR: Single quotes are not safely closed\033[0m\n");
		cmd->stop = 1;
		exit (0); // free tout stp
		//g_exit_value = 1;
		return (0);
	}
	(*i)++;
		printf("\033[0;32m ok Single quotes\033[0m\n");
	while (line[(*i)] != '\'' && line[(*i)])
	{
		line_after = ft_add_line_after(line_after, line[(*i)]);
		(*i)++;
	}
	(*i)++; 
	return (line_after);
}

//int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *str)
char	*ft_single_quote(char *line_after, int *i, char *line, t_cmd *cmd)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	return (stock_single_quote(cmd, i, line, line_after));
}


int	ft_single_quote_3(char *str, int *i, char *line, t_cmd *one_cmd)
{
	int		start;

	start = (*i);
	(*i)++;
	if (!ft_check_2rd_quote(&line[*i], '\''))
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
