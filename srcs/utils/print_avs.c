/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_avs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:03:55 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 14:05:06 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tab(char **av)
{
	int	j;

	j = 0;
	while (av[j])
	{
		printf("%s\n", av[j]);
		j++;
	}
}

void	print_mini_avs(t_mini *mini)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	cmd = mini->cmd;
	while (cmd)
	{
		printf(" 		%d commande = \n\n\033[0m", i);
		print_tab(cmd->av);
		if (cmd->file_in)
			printf("cmd->file_in exist\n");
		if (cmd->file_out)
			printf("cmd->file_out exist\n");
		i++;
		cmd = cmd->next;
	}
	return ;
}
