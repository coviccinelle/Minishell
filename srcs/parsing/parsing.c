/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/10 16:59:06 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
int	is_token(char *str, char *token)
{
	char	*res;

	res = strstr(str, token);
	if (res == NULL)
		return (0);
	return (1);
}*/

// there are 2 choices : put all in la liste chainee or tableau + liste chainee, depends on Marie-Ines
//Step 1: parsing espaces and avs
// step 2: counting (single and doubles) quotes
//  Step 3: tokenizing in liste chainee (2 ways: Balkis (tableau + liste chainee for each cmd) and Eclipse (liste chainee 100%))
int	parsing(t_mini *mini)
{
	int	k;
	t_mini	*tmp;

	tmp = mini;
	k = 0;
	if (ft_strchr(mini->line, '|'))
	{
		mini->i = ft_pars_piping(mini->line, mini);// = t_cmd *cmd
		while (tmp->next)
		{
			printf("printing tmp->line = %s\n\n", tmp->line);
			tmp = tmp->next;
		}
		while (k <= mini->i && mini)
		{
			ft_each_cmd(mini->line, mini);
			k++;
			mini = mini->next;
		}
		printf("%d\n", mini->i);
		return  (1);
	}
	else
	{
		printf("There's only one cmd! Simple\n");
		if (ft_each_cmd(mini->line, mini))
		{
			//mini->cmd = cmd;
			printf("OVER HERE : mini->cmd->av[0] = %s\n", mini->av[0]);
			return (1);
		}
	}
	return (0);
}

// init
int	malloc_node(t_mini	**one_cmd)
{
	t_mini	*new;
	
	new = (t_mini *)malloc(sizeof(t_mini));
	if (!new)
		return (0);
	if (!(*one_cmd))
	{
		new->next = NULL;
		*one_cmd = new;
		printf("after node\n");
	}
	return (1);
}

// ft_add_line_after
char	*ft_add_line_after(char *line, char buf)
{
	int		i;
	char	*new;

	if (line == NULL)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = buf;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(line);
	new = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf;
	new[++i] = '\0';
	free(line);
	return (new);
}

// ft_fill_av vs ft_malloc_avs
char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
