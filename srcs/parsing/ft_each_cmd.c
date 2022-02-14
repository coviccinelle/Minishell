/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/14 16:31:42 by thi-phng         ###   ########.fr       */
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

void	ft_pass_dquote(char *argv, int *i)
{
	if (argv[(*i) + 1] && (argv[(*i) + 1] == 34 || argv[(*i) + 1] == 39))
		(*i)++;
	else if (argv[(*i) + 1] && argv[(*i) + 1] == ' ')
	{
		(*i)++;
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	else if (argv[(*i) + 1] && (argv[(*i) + 1] == '<' || argv[(*i) + 1] == '>'))
		(*i)++;
	else if (argv[(*i)] == 34 && argv[(*i) + 1] && argv[(*i) + 1] != ' ')
		(*i)++;
}

int	mdquote3(char *argv, int *i)
{
	if (argv[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(argv, i);
	return (1);
}


int	ft_each_cmd(char *line, t_mini *one_cmd)
{
	int			i;
	char		*buf;
	char		*line_after;
	t_mini		*tmp;

	(void)buf;
//	(void)one_cmd;
	line_after = NULL;
	//tmp = NULL;
	if (!ft_init_each_cmd(one_cmd, &i, line))
		return (0);
	tmp = one_cmd;
	printf("Orgine line is : %s\n", line);
	while (line[i])
	{
		if (one_cmd->i > 0)
		{
			printf("pipe is not done\n\n");
			exit (0);
		}
		//euhhhh ...
		if (line[i] == ' ')
		{
			if (line_after)
				ft_avs(tmp, line_after);
			ft_space_skip(line, &i);
			line_after = NULL;
		}

		else if (line[i] == '"')
		{
			printf("1_Double quote found\n\n");
			printf("where am i ? line[i] = double quote found : %c\n", line[i]);
			line_after = ft_d2_quotes(line_after, &i, line, tmp);
			printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
			if (tmp->stop == 1)
				return (0);
			if (line_after == 0)
				break ;
			//dollar in quote
			if (!mdquote3(line, &i))
				break ;
			line_after = NULL;
		}
		else if (line[i] == '\'')
		{
			printf("single quotes\n\n");
			printf("line_after = %s\n", line_after);
			if (!ft_single_quote(line_after, &i, line, tmp))
				return (0);
			if (line[i + 1] == '\0')
				break ;//pass_quote?
			ft_pass_squote(line, &i);
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
