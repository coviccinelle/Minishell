/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_free_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:04:07 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/21 10:25:47 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void    ft_free_all_cmds(t_cmd *cmd)
{
    t_cmd   *tmp;
    
    while (cmd)
    {
        if (cmd->av)
            ft_free_tab(cmd->av);
        if (cmd->file)
            ft_free_file_red(cmd->file);
        cmd = cmd->next;
        free(tmp);
    }
    
}

void    ft_free_mini(t_mini *mini)
{
    t_mini  *tmp;

    if (mini)
    {
        tmp = mini;
        if (mini)
            ft_free_cmds(mini->cmd);
        free(tmp);
    }
}

