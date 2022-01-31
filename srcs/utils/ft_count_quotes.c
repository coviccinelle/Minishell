/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:30:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/31 15:30:03 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_count_quotes_char(const char *str, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == c)
            j++;
        i++;
    }
    return (j);
}

/*
int main()
{
    char    *str = "coucou em vit vit vu";
    char    c = 'v';
    
    printf("%d\n", ft_count_quotes_char(str, c));
    return (0);
}
*/

