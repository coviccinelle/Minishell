/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:10:27 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/07 21:45:15 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static int		len(long nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

char	*dolar_name(char *str, int *i, char *line_after, t_cmd *cmd)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	(*i)++;
	while (str[*i] && str[*i] != ' ')
	{
		line_after = ft_add_line_after(line_after, str[*i]);
		(*i)++;
	}
	return (line_after);
}

char	*dolar_2(char *str, int *i, char *line_after, char **envp)
{
	printf("LINE_AFTER %d\n", g_exit_value);
	if (line_after[0] == '?')
	{
		line_after = ft_itoa(g_exit_value);
		printf("LINE_AFTER Itoa %s\n", line_after);
		return (line_after);
	}
	line_after = ft_getenv(envp, line_after);
	if (str[*i])
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	return (line_after);
}
