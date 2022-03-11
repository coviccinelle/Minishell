/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/11 12:08:10 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pass_dquote(char *str, int *i)
{
	if (str[(*i) + 1] && (str[(*i) + 1] == 34 || str[(*i) + 1] == 39))
		(*i)++;
	else if (str[(*i) + 1] && str[(*i) + 1] == ' ')
	{
		(*i)++;
		while (str[(*i)] == ' ')
			(*i)++;
	}
	else if (str[(*i) + 1] && (str[(*i) + 1] == '<' || str[(*i) + 1] == '>'))
		(*i)++;
	else if (str[(*i)] == 34 && str[(*i) + 1] && str[(*i) + 1] != ' ')
		(*i)++;
}

int	quote_pass_2(char *str, int *i)
{
	if (str[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(str, i);
	return (1);
}

// more than 25 lines =>82 lignes
//if ret 0, ret 0 / quitte fonction ->free
//if ret 1, break
//if ret 2, continue / parsing ok

void	ft_init_param(t_param *param, char ***env, int *i)
{
	param->buf = NULL;
	param->var = NULL;
	param->env = env;
	param->i = *i;
}
