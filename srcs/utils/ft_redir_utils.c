/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:21:55 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 09:21:57 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_cmd *cmd)
{
    if (line[*i + 1] == '<' && line[*i] == '<')
    {
        cmd->type = HEREDOC;
        return ;
    }
    else if (line[*i] == '>' && line[(*i) + 1] == '>')
    {   
        cmd->type = APPEND; //d_right
        return ;
    }
    else if (line[*i] == '<' && line[(*i) + 1] != '<')
    {
        cmd->type = READONLY;//LEFT;
        return ;
    }
    else if (line[*i] == '>' && line[(*i) + 1] != '>')
    {
       cmd->type = TRUNC; //RIGHT;
        return ;
    }
}
