/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:13:00 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/13 20:36:15 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	all_are_digits(char *s)
{
	int	j;

	j = 0;
	if (s[0] == '-' || s[0] == '+')
		j++;
	if (all_digit(&s[j]))
		return (1);
	return (0);
}

unsigned char	ft_atoi(char *s)
{
	int					i;
	int					n;
	unsigned char		c;
	int					d;

	d = 1;
	i = 0;
	n = 0;
	if (s && (s[0] == '-' || s[0] == '+'))
	{
		if (s[0] == '-')
			d = -1;
		i++;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (s[i++] - '0');
	c = (unsigned char)(n * d);
	return (c);
}

int	exec_exit(int ac, char **av, char ***env)
{
	int	ret;
	(void)env;

	if (ac == 1)
	{
		printf("exit\n");
		ret = 0;
		//free_tab(env);
		exit(ret);
	}
	else if (!all_are_digits(av[1]))
	{
		//free_tab(env);
		ret = ft_puterror_fd("minishell: exit: ", \
				av[1], ":numeric argument required");
		exit(ret);
	}
	else if (all_are_digits(av[1]) && ac > 2)
		ret = ft_puterror_fd("minishell: exit: ", \
		"too many arguments", NULL);
	else if (all_are_digits(av[1]) && ac == 2)
	{
		printf("exit\n");
		//free_tab(env);
		ret = ft_atoi(av[1]);
		exit(ret);
	}
	return (ret);
}
