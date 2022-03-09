/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:21:52 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 13:03:02 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//stuff buf + \0
int	ft_buf(char *argv, int *i, char *buf)
{
	if (!argv[(*i)])
		return (0);
	buf[0] = argv[(*i)];
	buf[1] = '\0';
	(*i)++;
	return (1);
}

int	ft_fill_av(t_cmd *one_cmd, char **new, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (one_cmd->av[y])
	{
		new[y] = malloc(sizeof(char) * (ft_strlen(one_cmd->av[y]) + 1));
		if (!new[y])
			return (0);
		while (one_cmd->av[y][i])
		{	
			new[y][i] = one_cmd->av[y][i];
			i++;
		}
		new[y][i] = '\0';
		i = 0;
		y++;
	}
	new[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new[y])
		return (0);
	ft_strcpy(new[y], line);
	new[++y] = NULL;
	return (1);
}

void	free_avs(char **avs)
{
	int	i;

	i = 0;
	if (avs)
	{
		while (avs[i])
		{
			if (avs[i])
			{
				free(avs[i]);
				avs[i] = NULL;
			}
			i++;
		}
	}
	free(avs);
	avs = NULL;
}

char	**ft_malloc_avs(t_cmd *one_cmd, int len_tab, char *line)
{
	char	**new;

	if (len_tab == 0)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (0);
		new[0] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!new[0])
			return (0);
		ft_strcpy(new[0], line);
		new[1] = NULL;
		free(line);
		return (new);
	}
	new = malloc(sizeof(char *) * (len_tab + 2));
	if (!new)
		return (0);
	ft_fill_av(one_cmd, new, line);
	free(line);
	free_avs(one_cmd->av);
	return (new);
}

// to malloc and fill all avs in each structure mini
int	ft_avs(t_cmd *one_cmd, char *line_after)
{
	int	len_tab;

	len_tab = ft_len_avs(one_cmd->av);
	one_cmd->av = ft_malloc_avs(one_cmd, len_tab, line_after);
	if (!one_cmd->av)
		return (0);
	return (1);
}
