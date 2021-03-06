/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:38:44 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/15 13:41:03 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	safely_free(char **s1, char **s2);
char	*ft_strjoin_2(char *s1, char *s2);

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
	char	*name;

	name = NULL;
	(*i)++;
	while (str[*i] && str[*i] != ' ')
	{
		name = ft_add_line_after(name, str[*i]);
		(*i)++;
	}
	return (name);
}

void	dollar_quote_2(char **line_after, char **envp, char *dolar_value)
{
	char	*leak;
	char	*leak_2;

	leak = ft_getenv(envp, dolar_value);
	if (!*line_after)
		*line_after = ft_strdup("");
	leak_2 = *line_after;
	*line_after = ft_strxjoin(leak_2, leak, " ");
	if (leak)
		free(leak);
	if (leak_2)
		free(leak_2);
}

void	dollar_quote_1(char **line_after)
{
	char	*leak_0;

	leak_0 = *line_after;
	*line_after = ft_strjoin_2(*line_after, ft_itoa(g_exit_value));
	if (leak_0)
		free(leak_0);
}

char	*dolar_quote(char *str, char **envp)
{
	int		i;
	char	*line_after;
	char	*dolar_value;

	line_after = NULL;
	dolar_value = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			dolar_value = dolar_name_quote(str, &i);
			if (*dolar_value == '?')
				dollar_quote_1(&line_after);
			else
				dollar_quote_2(&line_after, envp, dolar_value);
			free(dolar_value);
		}
		else
		{
			line_after = ft_add_line_after(line_after, str[i]);
			i++;
		}
	}
	return (free(str), line_after);
}
