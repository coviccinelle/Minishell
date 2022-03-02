/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_me_vs_token_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:57:12 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/02 22:58:41 by thi-phng         ###   ########.fr       */
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
            return (1);
        i++;
    }
    return (0);
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

