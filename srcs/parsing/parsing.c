/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/22 10:02:08 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	malloc_node(t_cmd	**one_cmd)
{
	t_cmd	*new;
	
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	if (!(*one_cmd))
	{
		new->next = NULL;
		*one_cmd = new;
		printf("after node\n");
	}
	return (1);
}

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
char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
