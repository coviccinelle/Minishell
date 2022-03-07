/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:11:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/07 14:16:07 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_blank(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	rest_is_blank_2(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || str[i] == '|')
		return (0);
	while (str[i])
	{
		if (!is_blank(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	skip_blank(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	return (i);
}

int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	skip_blank_2(char *str, int *i, t_cmd *tmp, char *line_after)
{
	(void)tmp;
	(void)line_after;
	if (str[(*i)])
	{
		while (is_blank(str[*i]))
			(*i)++;
	}
	ft_avs(tmp, line_after);
}
