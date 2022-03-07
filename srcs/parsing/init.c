/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:07:21 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/07 19:00:07 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->line = NULL;
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
	(*mini)->stop = 0;
	(*mini)->line = NULL;
	(*mini)->env = NULL;
	(*mini)->fork = 0;
	(*mini)->ret_status = 0;
	(*mini)->heredoc = NULL;
	printf("done init mini\n");
}

void	init_shell(void)
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
	printf("Your user_name is : %s\n", getenv("USER"));
	sleep(1);
}
