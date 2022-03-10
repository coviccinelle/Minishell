/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 13:05:13 by thi-phng         ###   ########.fr       */
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

char	*ft_add_double_quote(int *i, char *line, char *line_after, char ***env)
{
	char *tmp;
	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("ERROR: Double quotes are not safely closed\n free tout stp\n");
		//free_tout_mini(mini);
		g_exit_value = 1003;
		return (NULL);
	}
	(*i)++;
	while (line[*i] != '"' && line[*i])
	{
		tmp = ft_add_line_after(line_after, line[*i]);
		line_after = tmp;
		(*i)++;
	}
	if (find_me('$', line_after) != -1)
		line_after = dolar_quote(line_after, *env);
	(*i)++;
	free(tmp);
	return (line_after);
}

// // DOUBLE QUOTES principales //
char	*ft_d2_quotes(char *line_aft, int *i, t_cmd *cmd, t_mini *mini, char ***env)
{
	char	*return_line;

	if (line_aft)
	{
		ft_avs(cmd, line_aft);
		line_aft = NULL;
	}
	return_line = ft_add_double_quote(i, mini->line, line_aft, env);
	if (!return_line && g_exit_value == 1003)
	{
		g_exit_value = 1;
		free(line_aft);
		free_one_cmd(cmd);
	}
	return (return_line);
}

char	*stock_single_quote(int *i, char *line, char *line_after)
{
	if (!ft_check_2rd_quote(&line[*i], '\''))
	{
		printf("ERROR: Single quotes are not safely closed\n free tout stp\n");
		g_exit_value = 1003;
		return (NULL);
	}
	(*i)++;
	while (line[*i] != '\'' && line[*i])
	{
		line_after = ft_add_line_after(line_after, line[*i]);
		(*i)++;
	}
	(*i)++;
	return (line_after);
}

//int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *str)
char	*ft_single_quote(char *line_after, int *i, char *line, t_cmd *cmd)
{

	char	*return_line;
	
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}

	return_line = stock_single_quote(i, line, line_after);
	if (!return_line && g_exit_value == 1003)
	{
		g_exit_value = 1;
		free(line_after);
		free_one_cmd(cmd);
	}
	return (return_line);
}
