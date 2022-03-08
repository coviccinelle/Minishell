/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:38:44 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/08 14:57:46 by thi-phng         ###   ########.fr       */
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
