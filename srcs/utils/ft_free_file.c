/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:24:21 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 21:24:29 by thi-phng         ###   ########.fr       */
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
