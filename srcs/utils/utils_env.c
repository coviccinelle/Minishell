/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:20:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/15 14:49:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	safely_free(char **s1, char **s2);

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
	safely_free(&s1, &s2);
	return (ret);
}

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
	d = strndup(&s[i], j);
	return (d);
}

//ajouter ft_strcmp pour mon failure cases dans mon export
