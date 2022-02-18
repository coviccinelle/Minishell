/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:36:01 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/18 16:02:22 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	address_quote(char *str, int c)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}


int	check_quote(char *str, int i)
{
	int	quote;

	//printf("\nchar ici est : str[i] %c\n", str[i]); 
	if (str[i] != '\'' && str[i] != '\"')
		return (0);
	quote = str[i++];
	//printf("place of i in quote = %d\n", i);
	//printf("quote = %c\n", quote);
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

int address_1st_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] == '\'') || (str[i] == '"'))
            return (i);
        i++;
    }
    return (-1);
}

int is_quote_err(char *str)
{
    int i;
    int k;

    i = 0;
    while (str[i])
    {
        k = address_1st_quote(str);
        if (k == -1)
            return (42); //not found any quote
        // found the first quote
        i += check_quote(str, k);
        if (address_1st_quote(&str[i]))
            check_quote_err(&str[i]);
        break ;
    }
    return (0);
}



int main(int ac, char **av)
{
	char *str = "hello coouou \"hihi\"babya hihi";
	(void)av;

	int 	a;

	// char **str_2;

	if (ac != 1)
		printf("errrr: wrong number of argument\n");
	//str_2 = ft_split_3(str, ' ');

    if (check_quote_err(str))
        printf("is no quote error\n");
    else
        printf("No quote error foudn\n");



	// a = address_quote(str, '"');
	// if (check_quote(str, a))
	// {
	// 	printf("\nadrress of the second quote is %d\n", check_quote(str, a));
	// 	printf("check quote ok, found the second one\n");
	// }
	// else
	// 	printf("ERROR: not found the second quote\n");

	// set_line(av[1], 0);
	// printf("done hihi\n");
    return (0);
}