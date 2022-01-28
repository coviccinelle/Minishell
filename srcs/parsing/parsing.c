/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/28 14:57:11 by thi-phng         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned long	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (str1 == str2)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}


int	detect_cmd(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str, "echo") == 0)
		{
			printf("\nECHO founded\n");
			return (1);
		}
		if (!ft_strcmp(str, "export"))
		{
			printf("\nEXPORT founded\n");
			return (1);
		}
		if (!ft_strcmp(str, "env"))
		{
			printf("\nENV founded\n");
			return (1);
		}
		if (!ft_strcmp(str, "exit"))
		{
			printf("\nEXIT founded\n");
			return (1);
		}
		if (!ft_strcmp(str, "cd"))
		{
			printf("\nCD founded\n");
			return (1);
		}
		if (!ft_strcmp(str, "pwd"))
		{
			printf("\nPWD founded\n");
			return (1);
		}
		if (!ft_strcmp(str, "unset"))
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
