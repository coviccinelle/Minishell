/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/21 11:58:38 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_token(char *str, char *token)
{
	char	*res;

	res = strstr(str, token);
	if (res == NULL)
		return (0);
	return (1);
}


int	detect_cmd(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (is_token(str, "echo"))
		{
			printf("\nECHO founded\n");
			return (1);
		}
		if (is_token(str, "export"))
		{
			printf("\nEXPORT founded\n");
			return (1);
		}
		if (is_token(str, "env"))
		{
			printf("\nENV founded\n");
			return (1);
		}
		if (is_token(str, "exit"))
		{
			printf("\nEXIT founded\n");
			return (1);
		}
		if (is_token(str, "cd"))
		{
			printf("\nCD founded\n");
			return (1);
		}
		if (is_token(str, "pwd"))
		{
			printf("\nPWD founded\n");
			return (1);
		}
		if (is_token(str, "unset"))
		{
			printf("\nUNSET founded\n");
			return (1);
		}
		i++;
	}
	return (0);
}



int	ft_init_mini(char *av, t_mini arg, char **env)
{
	arg.env = env;
	//arg.i = 0;
	arg.line = NULL;
	//arg.av = av;
	return (1);
}

int	ft_init_mini(t_mini a)
{
	a.builtin = 0;
	a.fork = 0;
	a.n_cmd = 0;
	a.n_pipes = 0;
	a.stop = 0;
	a.heredoc = 0;
	return (1);
}

int	ft_init(t_mini a, t_mini *arg, char *av, char **env)
{
	(void)a;
	(void)arg;
	(void)env;
	if (ft_init_mini(av, *arg, env))
		printf("done ft_init\n");
	if (ft_init_mini(a))
		printf("Done ft_init_mini\n");
	return (1);
}


int	parsing(char *av, t_mini *a, char **env)
{
	t_mini		arg;
	t_mini		*tmp;
	(void)tmp;
	(void)arg;
	(void)env;
	
	if (!ft_init(*a, &arg, av, env))
		return (0);	
//	tmp = a;
	while (av/*arg.av[arg.i]*/)
	{
		if (detect_cmd(av))
		{
			return (1);
		}
		return (0);
	}
	return (0);
}
