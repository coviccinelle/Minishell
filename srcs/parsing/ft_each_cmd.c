/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/22 19:16:52 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_init_each_cmd(t_cmd *cmd, int *i, char *line)
{

	if (!malloc_node(&cmd))
		return (0);
	cmd->next = NULL;
	(*i) = 0;
	ft_space_skip(line, i);
	return (1);
}


// THINGS TODO : 
//	- pipes
//	- redirections 


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

int	quote_pass_2(char *argv, int *i)
{
	if (argv[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(argv, i);
	return (1);
}

// int	ft_each_cmd(char *str, int *i, t_cmd *cmd)
// {
// 	char		*buf;
// 	char		*line_after;
// 	t_cmd		*tmp;
// 	char		*line;

// 	(void)buf;
// 	line = str;
// 	// printf("mini->line = %s\n", mini->line);
// 	line_after = NULL;
// 	//tmp = NULL;
// 	// if (!ft_init_each_cmd(cmd, &i, line))
// 	// 	return (0);
// 	tmp = cmd;
	
// 	printf("3. Inside each_cmd ^^ Orgine line is : %s\n", line);
// 	while (line[*i])
// 	{
		
// 		if (line[*i] == ' ')
// 		{
// 			if (line_after)
// 				ft_avs(cmd, line_after);
// 			(*i)++;
// 			ft_space_skip(line, i);
// 			//cmd->line = line_after;
// 			line_after = NULL;
// 		}
// 		if (line[*i] == '"')
// 		{
// 			printf("1_Double quote found\n\n");
// 			printf("where am i ? line[*i] = double quote found : %c\n", line[*i]);
// 			if (!ft_d2_quotes(line_after, i, line, tmp))
// 				return (0);
// 			printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
// 			if (line[(*i) + 1] == '\0')
// 				break ;
// 			//dollar in quote
// 			if (quote_pass_2(line, i))
// 				break ;
// 			line_after = NULL;
// 		}
// 		else if (line[*i] == '\'')
// 		{
// 			printf("single quotes\n\n");
// 			printf("line_after = %s\n", line_after);
// 			if (!ft_single_quote(line_after, i, line, tmp))
// 				return (0);
// 			if (line[(*i) + 1] == '\0')
// 				break ;
// 			ft_pass_squote(line, i);
// 			line_after = NULL;
// 		}
// 		else if (line[*i] == '$' && !(line[(*i) + 1] == '?'))
// 		{
// 			//line_after = ft_dollar_1(line, i, line_after, cmd);
// 			//line_after = ft_dollar_2(line, i, line_after, envp);
// 			printf("dollar sign but not $? non plus\n\n");
// 			ft_avs(tmp, line_after);
// 			line_after = NULL;
// 		}
// 		else if ((line[*i] == '<') || line[*i] == '>')
// 		{
// 			printf("Redirection\n\n");
// 		//	if (!ft_pars_redir(line_after, i, line, tmp)) //idea only
// 		//		return (0);
// 		}
// 		else
// 		{
// 			printf("Lettre is : %c\n", line[*i]);
// 			buf = malloc(sizeof(char) * 2);
// 			ft_buf(line, i, buf);
// 			line_after = ft_add_line_after(line_after, buf[0]);
// 			if (!line[*i] && line_after)
// 				ft_avs(cmd, line_after);
// 			free(buf);
// 		}
// 		//printf("cmd->av[0] = %s\n",cmd->av[0]);
// 	}
// 	return (1);
// }

int	ft_mredoc(char *line, int *i, char *argv, t_parsing *tmp)
{
	if (!ft_check_redoc(argv, (*i)))
	{
		printf("Minishell: syntax error near \
		unexpected token `newline'\n");
		return (0);
	}
	if (line)
	{
		ft_tabs(tmp, line);
		line = NULL;
	}
	ft_define_redicretcion(argv, i, tmp);
	ft_add_file(tmp, i, argv, line);
	if (!tmp->file)
		return (0);
	while (argv[(*i)] == ' ')
		(*i)++;
	line = NULL;
	return (1);
}


int	ft_each_cmd_4(t_mini *mini, char *line, int *i, t_cmd *cmd)
{
	char		*buf;
	char		*line_after;
	t_cmd		*tmp;

	(void)buf;
	(void)mini;
	line_after = NULL;
	tmp = cmd;
	
	printf("3. Inside each_cmd ^^ Orgine line is : %s\n", line);
	while (line[*i] && line[*i] != '|')
	{
		
		if (line[*i] == ' ')
		{
			if (line_after)
			{
				printf("line_after = %s\n", line_after);
				ft_avs(cmd, line_after);
				ft_print_av(cmd);
			}
			(*i)++;
			//ft_space_skip(line, i);
			//cmd->line = line_after;
			line_after = NULL;
		}
		if (line[*i] == '"')
		{
			printf("1_Double quote found\n\n");
			printf("where am i ? line[*i] = double quote found : %c\n", line[*i]);
			if (!ft_d2_quotes(line_after, i, line, tmp))
				return (0);
			printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
			if (line[(*i) + 1] == '\0')
				break ;
			//dollar in quote
			// if (!mdquote3(line, i))
			// 	break ;
			line_after = NULL;
		}
		else if (line[*i] == '\'')
		{
			printf("single quotes\n\n");
			printf("line_after = %s\n", line_after);
			if (!ft_single_quote(line_after, i, line, tmp))
				return (0);
			if (line[(*i) + 1] == '\0')
				break ;
			ft_pass_squote(line, i);
			line_after = NULL;
		}
		else if (line[*i] == '$' && !(line[(*i) + 1] == '?'))
		{
			//line_after = ft_dollar_1(line, i, line_after, cmd);
			//line_after = ft_dollar_2(line, i, line_after, envp);
			printf("dollar sign but not $? non plus\n\n");
			ft_avs(tmp, line_after);
			line_after = NULL;
		}
		else if (is_redir(line[*i]))
		{
			printf("Redirection\n\n");
			get_redir(mini, i, cmd);
			printf("done get_redir\n");
			if (cmd->type == HEREDOC || cmd->type == D_RIGHT)
				(*i)++;
			(*i)++;
			// if (!ft_pars_redir(line_after, i, line, tmp)) //idea only
			// 	return (0);
		}
		else if (line[*i] == '|')
		{
			if (line_after)
				ft_avs(cmd, line_after);
			break ;
		}
		else
		{
			//printf("Lettre is : %c\n", line[*i]);
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if (!line[*i] && line_after)
				ft_avs(cmd, line_after);
			free(buf);
		}
		//printf("cmd->av[0] = %s\n",cmd->av[0]);
	}
	return (1);
}

// void	ft_each_cmd_3(t_mini *mini, char *line, int *i, t_cmd *cmd)
// {
// 	char		*buf;
// 	char		*line_after;
// 	t_cmd		*tmp;
// //	char		*line;
// //	int			i;

// 	(void)buf;
// 	(void)mini;//mini will be used for $ in env
// //	i = 0;
// 	line_after = NULL;
// 	//cmd->line = str;

// 	tmp = cmd;
// 	printf("Orgine line is : %s\n", cmd->line);
// 	//line = cmd->line;
// 	while (line[*i] && line[*i] != '|')
// 	{
// 		if (line[*i] == ' ')
// 		{
// 			if (line_after)
// 				ft_avs(tmp, line_after);
// 			(i)++;
// 			//ft_space_skip(line, i);
// 			line_after = NULL;
// 		}
// 		else if (line[*i] == '"')
// 		{
// 			printf("1_Double quote found\n\n");
// 			printf("where am i ? line[*i] = double quote found : %c\n", line[*i]);
// 			if (!ft_d2_quotes(line_after, i, line, tmp))
// 				exit(0) ;
// 			printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
// 			if (line[(*i) + 1] == '\0')
// 				break ;
// 			//dollar in quote
// 			// if (!mdquote3(line, &i))
// 			// 	break ;
// 			line_after = NULL;
// 		}
// 		else if (line[*i] == '\'')
// 		{
// 			printf("single quotes\n\n");
// 			printf("line_after = %s\n", line_after);
// 			if (!ft_single_quote(line_after, i, line, tmp))
// 				exit(0);
// 			if (line[*i + 1] == '\0')
// 				break ;
// 			ft_pass_squote(line, i);
// 			line_after = NULL;
// 		}
// 		else
// 		{
// 			printf("char = %c\n", line[*i]);
// 			buf = malloc(sizeof(char) * 2);
// 			ft_buf(line, i, buf);
// 			line_after = ft_add_line_after(line_after, buf[0]);
// 			if (!line[*i] && line_after)
// 				ft_avs(tmp, line_after);
// 			free(buf);
// 		}
// 	}
// }

