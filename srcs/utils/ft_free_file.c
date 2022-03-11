/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:24:21 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/11 16:00:22 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_file(t_file **file)
{
	t_file	*tmp;

	tmp = *file;
	while ((*file))
	{
		tmp = (*file)->next;
		if ((*file)->name)
			free((*file)->name);
		free(*file);
		(*file) = tmp;
	}
}

void	free_tab_3(char **tab, int nrow)
{
	int	i;

	i = 0;
	while (i < nrow)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

//Function to free all cmds + mini + line_after
void	exit_custom(t_mini *mini, char *str, int n)
{
	(void)str;
	(void)mini;
	(void)n;
	printf("Free tout and exit stp\n");
}
