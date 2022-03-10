/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 11:53:25 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ft_add_line_after
char	*ft_add_line_after(char *line, char buf)
{
	int		i;
	char	*new;

	if (line == NULL)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = buf;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(line);
	new = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf;
	new[++i] = '\0';
	free(line);
	return (new);
}

//ft_fill_av vs ft_malloc_avs
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
