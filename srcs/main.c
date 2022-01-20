/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/20 19:46:04 by mloubet          ###   ########.fr       */
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
//	printf("");
	char *user_name = getenv("USER");
	printf("Your user_name is : %s\n", user_name);
	sleep(3);
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

void	env_struct(t_mini **mini, char **envp)
{
	t_mini	*tmp;

	tmp = *mini; 
//	t_env	*env;
//	t_export	*export;
	int	j;

	j = -1;
	while (envp[++j])
	{
		add_to_env(&tmp->env, envp[j], NULL, NULL); //ajout dans lordre denv
		//add_to_export_lst(&tmp->export_lst, env[j]) // ajout dans lordre asccii
	}
	//print_env(env)
	//print_export(export);
}

char	*ft_readline_input(char *line/*, char **env*/)
{
	//signal(SIGINT, ft_sigint);
	//signal(SIGQUIT, ft_sigquit);
	line = readline("\033[0;34m~Minishell$\033[0m ");
	if (!line)
		//ft_exit(NULL, env);
		printf("Ft_exit please\n");
	return (line);
}


int	main(int ac, char **av, char **envp)
{


	t_mini	*mini;

	mini = NULL;
	mini = malloc(40000);
//	env_struct(&mini, envp);
	//print_env(mini->env);


	

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
		line = ft_readline_input(line/*, env*/);
		printf("line = %s\n", line);
	//	line_history(line);
		if (line)
		{
			if (parsing(line/*, &param, env)*/))
			//	env = ft_exec_all_cmd(&param, env);
				printf("Parsing done -> Cmd found ! Allez on executer tout\n");
			else
				printf("No cmd found ! free the structure\n");//ft_free_params(&param);
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


