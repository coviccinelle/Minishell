/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/24 21:20:06 by thi-phng         ###   ########.fr       */
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
	printf("\e[1;1H\e[2J");
}

void	get_pwd()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Directory: %s", cwd);
}


char    *ft_strdup(const char *s1)
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
	//signal(SIGINT, ft_sigint);
	//signal(SIGQUIT, ft_sigquit);
	line = readline("\033[1;33m~Minishell$\033[0m ");
	if (!line)
		//ft_exit(NULL, env);
		printf("Ft_exit please\n");
	return (line);
}


void	ft_init_mini(t_mini mini)
{
	mini.env = NULL;
	mini.line = NULL;
	mini.ret = 0;
	mini.builtin = 0;
	mini.n_cmd = 0;
	mini.fork = 0;
	mini.pipes = 0;
	mini.heredoc = 0;
	mini.stop = 0;
	mini.next = NULL;
}


void	minishell(t_mini *mini)
{
	(void)mini;
	printf("minishell is not defined by now, pls come back later\n");
	//tous les cmd and exec
}

// Tham khao nha

// void	minishell_thamkhao(t_mini *mini)
// {
// 	t_token	*token;
// 	int		status;

// 	token = next_run(mini->start, NOSKIP);
// 	token = (is_types(mini->start, "TAI")) ? mini->start->next : token;
// 	while (mini->exit == 0 && token)
// 	{
// 		mini->charge = 1;
// 		mini->parent = 1;
// 		mini->last = 1;
// 		redir_and_exec(mini, token);
// 		status = WEXITSTATUS(status);
// 		mini->ret = (mini->last == 0) ? status : mini->ret;
// 		if (mini->parent == 0)
// 		{
// 			free_token(mini->start);
// 			exit(mini->ret);
// 		}
// 		mini->no_exec = 0;
// 		token = next_run(token, SKIP);
// 	}
// }


int	main(int ac, char **av, char **envp)
{
	t_mini		*mini;
	(void)av;
	//g_global_value_a _choisir = 0;

	mini = NULL;
	ft_init_mini(*mini);
	mini->env = ft_env_cpy(envp);
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	init_shell();
	while (mini->stop == 0)
	{
		mini->line = ft_readline_input(mini->line);
		add_history(mini->line);
		parsing(mini);
		if (mini->line)
			minishell(mini);
		//free_token(mini.line);
	}
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

