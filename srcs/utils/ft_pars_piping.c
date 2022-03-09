/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_piping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:08 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 13:45:16 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_av(t_cmd *mini)
{
	int	i;

	i = 0;
	while (mini->av[i] && i < (ft_len_avs(mini->av)))
	{
		printf("list av[%d] is = :%s\n\n", i, mini->av[i]);
		i++;
	}
}
