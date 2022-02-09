/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:30:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/09 16:09:23 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	**ft_copy_tab(char **env)
{
	int		i;
	int		size;
	char	**envp;

	i = -1;
	if (!env)
		return (NULL);
	size = nb_tabs(env);
	envp = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		envp[i] = strdup(env[i]); // A REMPLACER ! pourquoi ne repere pas mon ft_strdup ????
	envp[i] = NULL;
	return (envp);
}

void ft_putchar(int c)
{
	write(1, &c, 1);
}

void ft_putstr(char *s)
{
	int	i;

	i = -1;
	while(s[++i])
		write(1, &s[i], 1);
}
