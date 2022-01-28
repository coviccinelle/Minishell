/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/28 15:29:41 by thi-phng         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!n || str1 == str2)
		return (0);
	while (str1[i] && str2[i] && i < (n - 1) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}



int	detect_cmd(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str, "echo", 5) == 0)
		{
			printf("\nECHO founded\n");
			return (1);
		}
		if (!ft_strncmp(str, "export", 7))
		{
			printf("\nEXPORT founded\n");
			return (1);
		}
		if (!ft_strncmp(str, "env", 4))
		{
			printf("\nENV founded\n");
			return (1);
		}
		if (!ft_strncmp(str, "exit", 5))
		{
			printf("\nEXIT founded\n");
			return (1);
		}
		if (!ft_strncmp(str, "cd", 3))
		{
			printf("\nCD founded\n");
			return (1);
		}
		if (!ft_strncmp(str, "pwd", 4))
		{
			printf("\nPWD founded\n");
			return (1);
		}
		if (!ft_strncmp(str, "unset", 6))
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
		if (detect_cmd(&mini->line[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
