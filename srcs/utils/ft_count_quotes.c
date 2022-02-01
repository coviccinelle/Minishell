/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:30:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/02 00:18:02 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// count the number of the 1st quote apppeared
int ft_count_quotes_char(const char *str, char c, int i)
{
    int j;

    j = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            printf("Found the first one\n");
            j++;
            if (str[i + 1] == c)
            {
                j++;
                printf ("Found the second one\n");
                return (-3);
            }
        //    i++;
        }
        i++;
    }
    printf("ERRR: QUOTES NOT CLOSED\n");
    return (0);
}



int     find_second_quote(char *str, int *i, char c)
{
    while (str[*i])
    {
        if (str[*i] == c)
            return (*i);
        *i++;
    }
    return (0);
}

/*
int     ft_check_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        
        if (str[i] == '\'')
        {
            i = find_second_quote(str, &i, '\'');
            if (i == 0)
            {
                printf("ERR: Quote not closed safely\n");
                return (1);
            }
        }

        if (str[i] == '"')
        {
            printf("%c", str[i]);
            i = find_second_quote(str, &i, '"');
            if (i == 0)
            {
                printf("ERRR: Quote not closed safely\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}
*/

#include <string.h>

int ft_check_quote(char *s)
{
    int i = 0;
    char *str;
    while (s[i])
    {
        str = strsep(&s, "\"");
        printf("str = %s\n", str);
        i++;
    }
    return 0;
}
//-------------------------------------------------//

int ft_quotes(char *str, char c)
{
    int     i;
    int     q;
    //char    c;

    i = 1;
    q = 0;
    while (str[i])
    {
        printf("%c", str[i]);
        if (str[i] == c)
            q++;
        i++;
    }
    return (q);
}


int main()
{
    //char    *str = "echo 'c''ou\"c'ou \" em  vit  v'it vu";
    char str[500] = "bonjour \" 'hello'' 'grwgwrg' \"h\'i\'iii\" \"";
    
  //  printf("%d\n", ft_count_quotes_char(str, '\'', 0));
   printf("%d\n", ft_check_quote(str));
    return (0);
}