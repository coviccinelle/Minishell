/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/20 17:20:28 by thi-phng         ###   ########.fr       */
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



int	ft_init_env(char *av, t_env arg, char **env)
{
	arg.env = env;
	arg.i = 0;
	arg.line = NULL;
	arg.av = av;
	return (1);
}

int	ft_init_pars(t_pars a)
{
	a.is_builtin = 0;
	a.fork = 0;
	a.n_cmd = 0;
	a.n_pipes = 0;
	a.stop = 0;
	a.heredoc = 0;
	return (1);
}

int	ft_init(t_pars a, t_env *arg, char *av, char **env)
{
	(void)a;
	(void)arg;
	(void)env;
	if (ft_init_env(av, *arg, env))
		printf("done ft_init\n");
	if (ft_init_pars(a))
		printf("Done ft_init_pars\n");
	return (1);
}


int	parsing(char *av, t_pars *a, char **env)
{
	t_env		arg;
	t_pars		*tmp;
	(void)tmp;
	// (void)a;
	(void)arg;
	(void)env;
	
	if (!ft_init(*a, &arg, av, env))
		return (0);	
	//printf("%d\n", arg.av[arg.i]);
	printf("not segfaut please\n");
//	tmp = a;
	while (av/*arg.av[arg.i]*/)
	{
	
		if (detect_cmd(av))
		{
			printf("Detect_cmd successed\n");
			return (1);
		}
	}
	return (0);
}
