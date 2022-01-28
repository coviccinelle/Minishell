/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/28 14:29:47 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_token(char *str, char *token)
{
	char	*res;

	res = strstr(str, token);
	if (res == NULL)
		return (0);
	return (1);
}


int	detect_cmd(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (is_token(str, "echo"))
		{
			printf("\nECHO founded\n");
			return (1);
		}
		if (is_token(str, "export"))
		{
			printf("\nEXPORT founded\n");
			return (1);
		}
		if (is_token(str, "env"))
		{
			printf("\nENV founded\n");
			return (1);
		}
		if (is_token(str, "exit"))
		{
			printf("\nEXIT founded\n");
			return (1);
		}
		if (is_token(str, "cd"))
		{
			printf("\nCD founded\n");
			return (1);
		}
		if (is_token(str, "pwd"))
		{
			printf("\nPWD founded\n");
			return (1);
		}
		if (is_token(str, "unset"))
		{
			printf("\nUNSET founded\n");
			return (1);
		}
		i++;
	}
	return (0);
}



int	parsing(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->line[i])
	{
		while (mini->line[i] == ' ' || mini->line[i] == '\t')
			i++;
		if (detect_cmd(mini->line))
		{
			return (1);
		}
		return (0);
	}
	return (0);
}
