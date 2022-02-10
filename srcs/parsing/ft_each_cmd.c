/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/10 22:50:33 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_init_each_cmd(t_mini *one_cmd, int *i, char *line)
{

	if (!malloc_node(&one_cmd))
		return (0);
	one_cmd->next = NULL;
	(*i) = 0;
	ft_space_skip(line, i);
	return (1);
}


// THINGS TODO : 
//	- quotes
//	- pipes
//	- redirections 

// done double quote //
//single quote //

int	ft_each_cmd(char *line, t_mini *one_cmd)
{
	int			i;
	char		*buf;
	char		*line_after;
	t_mini		*tmp;

	(void)buf;
//	(void)one_cmd;
	line_after = NULL;
	tmp = NULL;
	if (!ft_init_each_cmd(one_cmd, &i, line))
		return (0);
	tmp = one_cmd;
	printf("Orgine line is : %s\n", line);
	if (one_cmd->av)
		free_avs(one_cmd->av);
	if (one_cmd->line)
		free(one_cmd->line);
	while (line[i])
	{
		if (one_cmd->i > 0)
		{
			printf("pipe is not done\n\n");
			exit (0);
		}
		if (line[i] == ' ')
		{
			if (line_after)
				ft_avs(tmp, line_after);
			ft_space_skip(line, &i);
			line_after = NULL;
		}

		else if (line[i] == '"')
		{
			printf("Double quote part 1\n\n");
			line_after = ft_d2_quotes(line_after, &i, line, tmp);
			if (tmp->stop == 1)
				return (0);
			if (line_after == 0)
				break ;
			//dollar in quote
			//end of line/quote
			line_after = NULL;
		}
		else if (line[i] == '\'')
		{
			printf("signle quotes\n\n");
			if (!ft_single_quote(line_after, &i, line, tmp))
				return (0);
			if (line[i + 1] == '\0')
				break ;//pass_quote?
			line_after = NULL;
		}
		else if (line[i] == '$' && !(line[i + 1] == '?'))
		{
			//line_after = ft_dollar_1(line, &i, line_after, one_cmd);
			//line_after = ft_dollar_2(line, &i, line_after, envp);
			printf("dollar sign but not $? non plus\n\n");
			ft_avs(tmp, line_after);
			line_after = NULL;
		}
		else if ((line[i] == '<') || line[i] == '>')
		{
			printf("Redirection\n\n");
		//	if (!ft_pars_redir(line_after, &i, line, tmp)) //idea only
		//		return (0);
		}
		else
		{
			//printf("a letter ");
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, &i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if (!line[i] && line_after)
				ft_avs(tmp, line_after);
			free(buf);
		}
	}
	return (1);
}
