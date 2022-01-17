/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/17 14:00:26 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av)
{
	read_from_terminal();
	break_into_tokens(); // break into words & operators obeying the quoting rules
	tokens_to_commands(); //simple commands, pipelines & lists
	shell_expansions(); //tokens to lists of files names, commands & arguments
	redirections(); // files truncate < > or append << >>
	execute_cmds(); //echo, export, unset, pwd, cd, env, exit
	exit_status();
	
	return (0);
}

