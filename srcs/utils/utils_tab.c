/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:32:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 16:35:33 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

//char	**ft_copy_tab(char **env);

// int	ft_strcmp(char *s, char *t)
// {
// 	while (*s && (*s == *t))
// 	{
// 		s++;
// 		t++;
// 	}
// 	return (*s - *t);
// }

void	print_export(char **tab)
{
	int	j;

	j = -1;
	while (tab[++j])
		printf("declare -x %s\n", tab[j]);
}

// plus print tab mais print env plutot vu que 
//je viens dajouter la condition strchr
int	print_env(char **env)
{
	int	j;

	j = -1;
	while (env[++j])
	{
		if (strchr(env[j], '=')) // a remplacer par ft_strchr
			printf("%s\n", env[j]);
	}
	return(1);
}

void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	ft_alphabetical_order_tab(char **env)
{
	char	**copy;
	int		i;
	int		j;

	copy = ft_copy_tab(env);
	i = 0;
	j = 0;
	while (copy[i])
	{
		j = i + 1;
		while (copy[j])
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
				swap(&copy[i], &copy[j]);
			j++;
		}
		i++;
	}
	print_export(copy);
	free_tab(&copy);
	return (0);
}
