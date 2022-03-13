/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/11 23:07:23 by mloubet          ###   ########.fr       */
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

char	*ft_add_double_quote(int *i, char *line, t_cmd *cmd, char ***env)
{
	char	*tmp;

	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("ERROR: Double quotes are not safely closed\n");
		g_exit_value = 1003;
		return (ft_strdup(""));
	}
	(*i)++;
	while (line[*i] != '"' && line[*i])
	{
		tmp = ft_add_line_after(cmd->la, line[*i]);
		cmd->la = tmp;
		(*i)++;
	}
	if (find_me('$', cmd->la) != -1)
		cmd->la = dolar_quote(cmd->la, *env);
	(*i)++;
	return (cmd->la);
}

// // DOUBLE QUOTES principales //
char	*ft_d2_quotes(int *i, t_cmd *cmd, t_mini *mini, char ***env)
{
	char	*return_line;

	if (cmd->la)
	{
		ft_avs(cmd, cmd->la);
		cmd->la = NULL;
	}
	return_line = ft_add_double_quote(i, mini->line, cmd, env);
	if (!return_line && g_exit_value == 1003)
	{
		g_exit_value = 1;
	//	free(cmd->la);
	//	free_one_cmd(cmd);
	}
	return (return_line);
}

char	*stock_single_quote(int *i, char *line, char *line_after)
{
	if (!ft_check_2rd_quote(&line[*i], '\''))
	{
		printf("ERROR: Single quotes are not safely closed\n");
		g_exit_value = 1003;
		return (ft_strdup(""));
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
char	*ft_single_quote(int *i, char *line, t_cmd *cmd)
{
	char	*return_line;

	if (cmd->la)
	{
		ft_avs(cmd, cmd->la);
		cmd->la = NULL;
	}
	return_line = stock_single_quote(i, line, cmd->la);
	if (!return_line && g_exit_value == 1003)
	{
		g_exit_value = 1;
		free(cmd->la);
		free_one_cmd(cmd);
	}
	return (return_line);
}
