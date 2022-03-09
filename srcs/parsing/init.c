/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:32:04 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 21:31:53 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->av = NULL;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->last_file_in = NULL;
	cmd->last_file_out = NULL;
	cmd->next = NULL;
}

void	ft_init_mini(t_mini **mini)
{
	(*mini)->pipe = 0;
	(*mini)->line = NULL;
	(*mini)->fork = 0;
	(*mini)->ret_status = 0;
}

void	init_shell(void)
{
	char	*user_name;

	user_name = getenv("USER");
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
	//printf("");
	printf("Your user_name is : %s\n", user_name);
	sleep(1);
}
