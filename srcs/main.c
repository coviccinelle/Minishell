/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/08 22:37:59 by thi-phng         ###   ########.fr       */
=======
/*   Updated: 2022/02/09 11:21:34 by mloubet          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell()
{
	printf("\e[1;1H\e[2J");
	printf("Welcome to our mini-tiny-shell made by Marie-Ines and Thao\n");
	printf("Attention: Version demo.00\n");
	printf("        ,----,\n");
    printf("   ___.`      `,\n");
    printf("   `===  D     :\n");
    printf("     `'.      .'\n");
    printf("        )    (                   ,\n");
    printf("       /      \\_________________/|\n");
    printf("      /                          |\n");
    printf("     |         MINISHELL         ;\n");
    printf("     |               _____       /\n");
    printf("     |      \\       ______7    ,'\n");
    printf("     |       \\    ______7     /\n");
    printf("      \\       `-,____7      ,'   by Marie-Ines & Thao\n");
    printf("^~^~^~^`\\                  /~^~^~^~^\n");
    printf("  ~^~^~^ `----------------' ~^~^~^\n");
    printf(" ~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n");
    printf("\n");
    printf("\n");
    printf("\n");
	printf("");
	char *user_name = getenv("USER");
	printf("Your user_name is : %s\n", user_name);
	sleep(1);
//	printf("\e[1;1H\e[2J");
}

void	get_pwd()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Directory: %s", cwd);
}

char    *ft_strdup(char *s1)
{
        char    *str;
        int             i;
        int             size;

        size = 0;
        while (s1[size])
        {
                size++;
        }
        str = malloc((size + 1) * sizeof(char));
        if (!str)
                return (NULL);
        i = 0;
        while (s1[i])
        {
                str[i] = s1[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

char	**ft_env_cpy(char **envp)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	i = 0;
	while (envp[i++])
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

char	*ft_readline_input(char *line)
{
	signal(SIGINT, ft_sigint_ctr_c);
	signal(SIGQUIT, ft_sigquit_ctr_bs);
	line = readline("\033[1;33m~Minishell$\033[0m ");
	//add_history(line);
	if (!line)
	{
		printf("Oops someone just typed ctr^D?!? Bye, I'm out < 0_0 >\n");
		exit(0);
	}
	return (line);
}

void	ft_init_mini(t_mini *mini)
{
	mini->env = NULL;
	mini->line = NULL;
	mini->i = 0;
	mini->stop = 0;
	mini->av = NULL;
	mini->ac = 0;
	mini->cmd_line = NULL;
	mini->n_cmd = 0;
	mini->ret = 0;
	mini->builtin = 0;
	mini->pipe = 0;
	mini->fork = 0;
	mini->quote = 0;
	mini->d_quotes = 0;
	mini->heredoc = 0;
	mini->type = NOPE;
	mini->file = NULL;
	mini->next = NULL;
	mini->ret_status = 0;
	printf("done init mini\n");
}

void	minishell_exec_cmds(t_mini *mini)
{
	(void)mini;
	int		i;
	int		ac;
	int		status;
	//char	**av;
//	char	**env;

	i = 0;
	/*while(mini->av[i])
	{
		printf("all av[%d] [%s]\n", i, mini->av[i]);
		i++;
	}
	*/
	// i = 0;
	// if (!detect_cmd(mini->av[0]))
	// 	return (0);
	//av = mini->av;
	// 	printf(" PRINT AV \n\n\n");
	// print_env(av);
	ac = nb_tabs(mini->av);
	while (i <= ac)
	{
		printf("Print av[%d] = %s\n\n", i, mini->av[i]);
		i++;
	}
	
//	env = mini->env;
<<<<<<< HEAD
	pid_t   father;
    father = fork();
	int stat;
    if (father == 0)
    {
		exec_cmd(nb_tabs(mini->av), mini->av, &mini->env);
		//exit(0);
	}
	waitpid(father, &stat, 0);
	if (stat == 4202397)
		stat = 127;
	printf("ret is: %d\n", stat);
=======
	if (is_builtin(mini->av[0])) //a remplacer par av[0] apres.
		exec_builtin(mini->av[0], nb_tabs(mini->av), mini->av, &mini->env);
	else
	{
		pid_t   father;

		father = fork();
		if (father > 0)
		{
			waitpid(-1, &status, 0);
			printf("I AM YOUR FATHER\n");
		}
		if (father == 0)
		{
			sleep(1);
			exec_cmd(nb_tabs(mini->av), mini->av, &mini->env);
			exit(0);
		}
//	exec_cmd(ac, av, &env);
	//printf("\n\033[1;33m  oopps...	~Minishell$\033[0m  is not defined by now, pls come back later\n");
	//tous les cmd and exec
	}
>>>>>>> main
}

void	free_tab2(char **tab)
{
	int	j;
	
	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	tab = NULL;
}

void	ft_free_cmd(t_mini *cmd)
{
	t_mini	*tmp;

	if (!cmd)
		printf("haha \n");
	while (cmd)
	{
		tmp = cmd;
		//if (cmd->file)
		//	ft_free_file(cmd->file)
		if (*cmd->av)
			free_tab(&cmd->av);
		cmd = cmd->next;
		printf("we will we will rock you\n");
		//ft_free_cmd(tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mini		mini;
	(void)av;

//	g_n_exit = 0;

	//mini = NULL;
	ft_init_mini(&mini);
	mini.env = ft_env_cpy(envp);
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	init_shell();
	while (mini.stop == 0)
	{
		mini.line = ft_readline_input(mini.line);
		add_history(mini.line);
		while (42)
		{
			if (parsing(&mini))
			{
				if (mini.av)
				{
					printf("mini->av exist\n\n");
					minishell_exec_cmds(&mini);
					mini.av = NULL;
					//free_tab(&mini.av);
				}	
			
			//	printf("ici 1 done parsing\n");
				//free_tab(&mini.av);
				//ft_free_cmd(&mini);
				break ;
			}
			else
			{
				printf("ici 2 parsing return 0 = free\n");
				//ft_free_cmd(&mini);
				if (mini.av)
					printf("i'm here\n");
				free_tab(&mini.av);
				//free mini->cmd
				break ;
			}
			free(mini.line);
		}
	//	ft_free_cmd(&mini);
		//free_tokens_and_structure(&mini);
	}
	//free(line);
	//free_env(mini.env);
	return(0);

//		read_from_terminal();
		//break_into_tokens(); // break into words & operators obeying the quoting rules
		//tokens_to_commands(); //simple commands, pipelines & lists
		//shell_expansions(); //tokens to lists of files names, commands & arguments
		//redirections(); // files truncate < > or append << >>
		//execute_cmds(); //echo, export, unset, pwd, cd, env, exit
		//exit_status();
}
