/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:20:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 14:22:51 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_var_name(char *av)
{
	int	i;

	i = -1;
	if (is_digit(av[0]))
		return (0);
	while (av[++i])
	{
		if ((!is_digit(av[i])) && (!is_alpha(av[i]) && av[i] != '_'))
			return (0);
	}
	return (1);
}

// pour trouver indice ou jai mon char.
int	chpos(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (-1);
		str++;
	}
	return (str - s);
}

char	*ft_strndup(char *s, int n)
{
	int		len;
	char	*copy;

	len = 0;
	while (s[len] && len < n)
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}

/*
char	*ft_strndup(char *s, int n)
{
	char			*res;
	int	i;

	i = 0;
	res = malloc(sizeof(char) * n) + 1;
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}
*/

char	*cpy_trim(char *s, char from, char to)
{
	int		i;
	int		j;
	char	*d;

	d = NULL;
	i = chpos(s, from);
	j = chpos(s, to);
	if (i == -1 || j == -1)
		return (ft_strdup(s));
	if (from == '=')
		i = i + 1;
	d = ft_strndup(&s[i], j);
	return (d);
}

//ajouter ft_strcmp pour mon failure cases dans mon export
