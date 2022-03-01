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

	//if (ft_syntax_error(mini->cmd) == ERROR)
	// {
	// 	printf("Free tout in mini->line and things you malloc stp!\n");
	// 	return ;
	// }
	mini->cmd = stock_cmds(mini);
	if(!mini->cmd || !mini->cmd->av)
		return ;
	cmd = mini->cmd;
	printf("!!!!nb_cmds = %d\n\n", nb_cmds(mini->cmd));
	if (nb_cmds(mini->cmd) == 1)
		exec_cmd_with_no_pipe(mini);
	else
		run_piped_cmds(mini,  nb_cmds(mini->cmd));
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
	//	line = NULL;
		line = ft_readline_input(mini->line);
		add_history(line);
		mini->line = line;
		if (mini->line)
			mini_run(mini);
		if (mini->cmd->av)
			print_mini_avs(mini);
		//free(mini);
		//free(line);
	}
	//free_tab(&mini->env); // a free mais ne veut pas pour linstant
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

