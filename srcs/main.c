/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:13:09 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 21:20:15 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline_input(char *line, char ***env, t_mini *mini)
{
	(void)mini;
	signal(SIGINT, ft_sigint_ctr_c);
	signal(SIGQUIT, ft_sigquit_ctr_bs);
	line = readline("\033[1;33m~🌈 Minishell 🌻$\033[0m ");
	if (!line)
	{
		if (*env)
			printf("FREE TAB NE MARCHE PAS\n\n");
		//printf("Oops someone just typed ctr^D?!? Bye, I'm out < 0_0 >\n");
		exit(0);
	}
	return (line);
}

int	mini_run(t_mini *mini, char ***env)
{
	mini->cmd = stock_cmds(mini, env);
	if (!mini->cmd || !mini->cmd->av)
	{
		return (0);
	}
	if (nb_cmds(mini->cmd) == 1)
	{
		exec_cmd_with_no_pipe(mini, env);
		return (1);
	}
	else
	{
		run_piped_cmds(mini, env);
		return (1);
	}
}

void	ft_copy_env(char ***s, char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i++;
	(*s) = malloc(sizeof(char *) * (i + 1));
	if (!*s)
		return ;
	i = -1;
	while (v[++i])
		(*s)[i] = ft_strdup(v[i]);
	(*s)[i] = NULL;
}

void	minishell(char **env)
{
	t_mini		*mini;
	char		*line;
	
	ft_init_mini(&mini);
	ft_copy_env(&(env), env);
	init_shell();
	line = NULL;
	while (42)
	{
		line = ft_readline_input(mini->line, &env, mini);
		if(!line)
			exit(130);
		add_history(line);
		mini->line = line;
		if (mini->line || mini->cmd->av)
		{
			if (mini_run(mini, &env) == 0)
			{
				free_tout_mini(mini);
				exit (1);
			}
		}
		unlink("heredoc");
		//if (line)
		//	free(line);
		//ft_free_cmds(mini);
		// if(line)
		// 	free(line);
	//	free_tab(&env);
		free_tout_mini(mini);
	}
}

int	g_exit_value;

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	minishell(env);
	return (0);
}
