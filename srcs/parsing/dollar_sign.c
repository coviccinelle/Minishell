/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:30:50 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/08 14:30:53 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*dolar_name(char *str, int *i, char *line_after, t_cmd *cmd)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	(*i)++;
	while (str[*i] && str[*i] != ' ')
	{
		line_after = ft_add_line_after(line_after, str[*i]);
		(*i)++;
	}
	return (line_after);
}

char	*dolar_2(char *str, int *i, char *line_after, char **envp)
{
	line_after = ft_getenv(envp, line_after);
	if (str[*i])
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	return (line_after);
}
