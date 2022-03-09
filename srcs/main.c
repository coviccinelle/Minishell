/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:13:09 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 09:16:14 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline_input(char *line)
{
	signal(SIGINT, ft_sigint_ctr_c);
	signal(SIGQUIT, ft_sigquit_ctr_bs);
	line = readline("\033[1;33m~🌈 Minishell 🌻$\033[0m ");
	if (!line)
	{
		printf("Oops someone just typed ctr^D?!? Bye, I'm out < 0_0 >\n");
		exit(0);
	}
	return (line);
}

void	mini_run(t_mini *mini)
{
	t_cmd	*cmd;

	mini->cmd = stock_cmds(mini);
	if (!mini->cmd || !mini->cmd->av)
	{
		ft_free_cmds(mini);
		return ;
	}
	cmd = mini->cmd;
	if (nb_cmds(mini->cmd) == 1)
		exec_cmd_with_no_pipe(mini);
	else
		run_piped_cmds(mini, nb_cmds(mini->cmd));
	//free(cmd->line);
	ft_free_cmds(mini);
}

void	ft_copy_env(char ***s, char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i++;
	(*s) = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (v[++i])
		(*s)[i] = ft_strdup(v[i]);
	(*s)[i] = NULL;
}

// my_new_version :
void	minishell(char **env)
{
	t_mini		*mini;//data
	char		*line;//data_parsing
	
	ft_init_mini(&mini);
	mini->env = NULL;
//	mini->env = ft_env_cpy(env);
	ft_copy_env(&(mini->env), env);
	//mini->env = env;
	init_shell();
	line = NULL;
	while (42)
	{
		line = ft_readline_input(mini->line);
		add_history(line);
		mini->line = line;
		if (mini->line || mini->cmd->av)
			mini_run(mini);
		unlink("heredoc");
		if (line)
			free(line);
//	ft_free_cmds(mini);
	}
	free_tab(&(mini->env));
//	free(mini);
	//free(line);
}

int	g_exit_value = 0;

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	minishell(env);
	return (0);
}
