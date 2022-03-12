/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:38:44 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/11 23:25:31 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		e;

	i = -1;
	e = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!ret)
		return (NULL);
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[e])
	{
		ret[i + e] = s2[e];
		e++;
	}
	ret[i + e] = ' ';
	e++;
	ret[i + e] = '\0';
	free(s1);
	if (s2)
		free(s2);
	return (ret);
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
/*
char	*dolar_quote(char *str, char **envp)
{
	int		i;
	char	*line_after;
	char	*dolar_value;
	char 	*another_value;

	line_after = NULL;
	dolar_value = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			dolar_value = dolar_name_quote(str, &i);
			if (*dolar_value == '?')
				line_after = ft_strjoin_2(line_after, ft_itoa(g_exit_value));
			another_value = ft_getenv(envp, dolar_value);
			free(dolar_value);
			line_after = ft_strjoin_2(line_after, another_value);
		}
		else
		{
			another_value = ft_add_line_after(ft_strdup(line_after), str[i]);
		//	free(line_after);
			i++;
		}
	}
	free(str);
	return (another_value);
}
*/




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
			{
				char *leak_0 = line_after;
				line_after = ft_strjoin_2(line_after, ft_itoa(g_exit_value));
				if (leak_0)
					free(leak_0);
			}
			else
			{
				char	*tmp = dolar_value;
				dolar_value = ft_getenv(envp, tmp);
				line_after = ft_strxjoin(line_after, dolar_value, " ");
				free(tmp);
			}
			free(dolar_value);
		}
		else
		{
			printf("JE PASSE ICI\n\n");
			line_after = ft_add_line_after(line_after, str[i]);
			i++;
		}
	}
	free(str);
	return (line_after);
}
