/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/23 10:26:07 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_pwd()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Directory: %s", cwd);
}

char	*ft_readline_input(char *line)
{
	signal(SIGINT, ft_sigint_ctr_c);
	signal(SIGQUIT, ft_sigquit_ctr_bs);
	line = readline("\033[1;33m~🌈 Minishell 🌻$\033[0m ");
	//add_history(line);
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

	//printf("1. Start minishell\n");
	mini->cmd = stock_cmds_2(mini);
	//printf("3. Done stocking cmds\n");
	cmd = mini->cmd;
	//printf("4. done cmd = mini->cmd\n");
	while (cmd->next)
	{
		if (cmd->av)
		{
			printf("cmd->av EXISTE, mini->line = %s \n", cmd->line);
		}
		if (is_builtin_2(mini, cmd))
		{
			printf("\nBuitins\n");
			//minishell_exec_cmds(cmd, mini);
			run_builtin(mini, cmd);
		}
		else
		{
			printf("\nNot buitins\n");
			run_execve_2(mini, cmd);
		//if (mini->ret_status == 130)
		//	break ;
		}
		cmd = cmd->next;
	}
	//ft_free_cmds(mini);
	printf("Idk, free tout : in main/mini_run\n");
	free(cmd->line);
}

// my_new_version :
void	minishell(char **env)
{
	t_mini		*mini;//data
	char		*line;//data_parsing

	ft_init_mini(&mini);
	mini->env = ft_env_cpy(env);
	init_shell();
	while (42)
	{
		line = ft_readline_input(mini->line);
		add_history(line);
		mini->line = line;
		if (mini->line)
			mini_run(mini);
		print_mini_avs(mini);
		//free(mini);
		//free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	minishell(env);
	return (0);
}

