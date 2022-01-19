/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/19 18:15:08 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	sleep(5);
	printf("\e[1;1H\e[2J");
}

void	get_pwd()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Directory: %s", cwd);
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
		if (find_me(str[i], "ecpu"))
		{
			if (str[i] == 'e' && is_token(str, "echo"))
				return (1);
			if (str[i] == 'e' && is_token(str, "export"))
				return (1);
			if (str[i] == 'e' && is_token(str, "env"))
				return (1);
			if (str[i] == 'e' && is_token(str, "exit"))
				return (1);
			if (str[i] == 'c' && is_token(str, "cd"))
				return (1);
			if (str[i] == 'p' && is_token(str, "pwd"))
				return (1);
			if (str[i] == 'u' && is_token(str, "unset"))
				return (1);
		}
	}
	return (0);
}

int	parsing(char *line/*, t_parsing param, char **env*/)
{
	if (detect_cmd(line))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**env;
	//t_parsing	param;

	//g_global_value_a _choisir = 0;
	(void)av;
	line = NULL;
	env = ft_env_cpy(envp);
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	init_shell();
	while (1)
	{
		line = readline_input(line);
	//	line_history(line);
		if (line)
		{
			if (parsing(line/*, &param, env*/))
			//	env = ft_exec_all_cmd(&param, env);
				printf("Allez on executer tout\n");
			else
				printf("free the structure\n");//ft_free_params(&param);
		}
	}
	printf("Freeeee all tabs pls\n");
//	free_everything(env);
	return (0);

//		read_from_terminal();
		//break_into_tokens(); // break into words & operators obeying the quoting rules
		//tokens_to_commands(); //simple commands, pipelines & lists
		//shell_expansions(); //tokens to lists of files names, commands & arguments
		//redirections(); // files truncate < > or append << >>
		//execute_cmds(); //echo, export, unset, pwd, cd, env, exit
		//exit_status();
}


