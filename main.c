/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/18 18:51:03 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell()
{
	printf("\e[1;1H\e[2J");
//	clear();
	printf("Welcome to our mini-tiny-shell made by Marie-Ines and Thao\n");
	printf("Attention: Version demo ver.00\n");
	char *user_name = getenv("USER");
	printf("Your user_name is : %s\n", user_name);
	sleep(10);
	//clear();
	printf("\e[1;1H\e[2J");
}

void	get_pwd()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Directory: %s", cwd);
}

int		main(/*int ac, char **av, char **env*/)
{
	char	input_str[1000];
	init_shell();
	
	while (1)
	{
		get_pwd();
		if (readline_input(input_str))
			continue;
		
//		read_from_terminal();
		//break_into_tokens(); // break into words & operators obeying the quoting rules
		//tokens_to_commands(); //simple commands, pipelines & lists
		//shell_expansions(); //tokens to lists of files names, commands & arguments
		//redirections(); // files truncate < > or append << >>
		//execute_cmds(); //echo, export, unset, pwd, cd, env, exit
		//exit_status();
	}
	return (0);
}

