/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/03 00:07:52 by thi-phng         ###   ########.fr       */
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
		while (str[*i] == ' ')
			(*i)++;
	}
	else if (str[*i] == 39 && str[(*i) + 1] && str[(*i) + 1] != ' ')
		(*i)++;
}

char	*dolar_name_quote(char *str, int *i)
{
	char *name;
	
	name = NULL;
	(*i)++;
	while (str[*i] && str[*i] != ' ')
	{
		name = ft_add_line_after(name, str[*i]);
		(*i)++;
	}
	return (name);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ret;
	size_t	i = 0, e = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[e])
	{
		ret[i] = s2[e];
		e++;
		i++;
	}
	ret[i] = ' ';
	i++;
	ret[i] = '\0';
	free(s1);
	return (ret);
}

char *dolar_quote(char *str, char **envp)
{
	int	i;
	char *line_after = NULL;
	char *dolar_value = NULL;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dolar_value = dolar_name_quote(str, &i);
			dolar_value = ft_getenv(envp, dolar_value);
			line_after = ft_strjoin_2(line_after, dolar_value);
		}
		else
			line_after = ft_add_line_after(line_after, str[i]);
		i++;
	}
	return (line_after);
}

char	*ft_add_double_quote(t_cmd *cmd, int *i, char *line, char *line_after, t_mini *mini)
{
	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("\033[0;31m ERROR: Double quotes are not safely closed\033[0m\n");
		cmd->stop = 1;
		exit (0); // free tout stp
		//g_exit_value = 1;
		return (0);
	}
	printf("\033[0;32m ok Double quotes\033[0m\n");
	(*i)++;
	while (line[*i] != '"' && line[*i])
	{
		line_after = ft_add_line_after(line_after, line[*i]);
		(*i)++;
	}
	if (find_me('$', line_after) != -1)
		line_after = dolar_quote(line_after, mini->env);
	(*i)++;
	return (line_after);
}

// // DOUBLE QUOTES principales //
char	*ft_d2_quotes(char *line_after, int *i, char *line, t_cmd *cmd, t_mini *mini)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	return (ft_add_double_quote(cmd, i, line, line_after, mini));
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
	while (line[*i] && line[*i] != '\'')
	{
		str = ft_add_line_after(str, line[*i]);
		(*i)++;
	}
	if (str)
		ft_avs(one_cmd, str);
	return (1);
}
