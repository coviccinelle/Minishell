/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:23:19 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 09:23:45 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_diff(char *str)
{
	int	i;
	int	quote_type;

	i = 1;
	quote_type = str[i++];
	while (str[i] && str[i] != quote_type)
		i++;
	return (i);
}

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

void	skip_blank_2(char *str, int *i, t_cmd *tmp, char *line_after)
{
	if (str[(*i)])
	{
		while (is_blank(str[*i]))
			(*i)++;
	}
	if (line_after)
		ft_avs(tmp, line_after);
}
