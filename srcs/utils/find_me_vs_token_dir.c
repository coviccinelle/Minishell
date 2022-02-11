/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_me_vs_token_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:57:12 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/09 15:11:28 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int find_me(char c, char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int is_token_char(char c)
{
    if (c == '|')
        return (1);
    if (c == '<')
        return (1);
    if (c == '>')
        return (1);
    return (0);
}
