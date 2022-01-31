/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:30:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/31 17:09:35 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// count the number of the 1st quote apppeared
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

// detect the first quote appeared
char ft_detect_quote(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
            return (str[i]);
        i++;
    }
    return ('\0');
}

// pair ou impair of the 1st quote appeared
int ft_count_quotes(const char *str)
{
    char    c;

    c = ft_detect_quote(str);
    if (*str)
    {
        if (ft_count_quotes_char(str, c) % 2 != 0)
            return(-1);
    }
    return (0);
}


int main()
{
    char    *str = "echo 'coucou  \" em ' vit vit vu";
    
    printf("%d\n", ft_count_quotes(str));
    return (0);
}