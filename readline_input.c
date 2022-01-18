/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:52:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/18 18:13:09 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int readline_input(char *str)
{
    char    *buffer;
    
    buffer = readline("\n");
    if (strlen(buffer))
    {
        add_history(buffer);
        strcpy(str, buffer);
        return (0);
    }
    else
    {
        return (1);
    }
}