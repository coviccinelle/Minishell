/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/03 16:02:15 by mloubet          ###   ########.fr       */
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

void	ft_pass_dquote(char *str, int *i)
{
	if (str[(*i) + 1] && (str[(*i) + 1] == 34 || str[(*i) + 1] == 39))
		(*i)++;
	else if (str[(*i) + 1] && str[(*i) + 1] == ' ')
	{
		(*i)++;
		while (str[(*i)] == ' ')
			(*i)++;
	}
	else if (str[(*i) + 1] && (str[(*i) + 1] == '<' || str[(*i) + 1] == '>'))
		(*i)++;
	else if (str[(*i)] == 34 && str[(*i) + 1] && str[(*i) + 1] != ' ')
		(*i)++;
}

int	quote_pass_2(char *str, int *i)
{
	if (str[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(str, i);
	return (1);
}


int	ft_add_to_fstack_out(t_cmd **cmd, char *line)
{
	t_file		*tmp;
	t_file		*new;
	t_file		*p;

	tmp = (*cmd)->file_out;
	p = (*cmd)->file_out;
	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return (0);
	new->next = NULL;
	new->name = ft_strdup(line);
	new->type = (*cmd)->type;
	if (!(*cmd)->file_out)
		(*cmd)->file_out = new;
	else
	{
		while(p && p->next)
			p = p->next;
		p->next = new;
	}
	return (1);
}

int	ft_add_to_fstack_in(t_cmd **cmd, char *line)
{
	t_file		*tmp;
	t_file		*new;
	t_file		*p;

	tmp = (*cmd)->file_in;
	p = (*cmd)->file_in;
	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return (0);
	new->next = NULL;
	new->name = strdup(line); // a remplacer par ft_strdup
	new->type = (*cmd)->type;
	if (new->type == HEREDOC)
	{
		call_heredoc(new->name);
		//unlink(new->name);
	}
	if (!(*cmd)->file_in)
		(*cmd)->file_in = new;
	else
	{
		while(p && p->next)
			p = p->next;
		p->next = new;
	}
	return (1);
}




int	ft_add_file_out(t_cmd **cmd, int *i, char *str, char *line)
{
	while (is_redir(str[*i]) || is_blank(str[*i]))
		(*i)++;
	while (!is_blank(str[*i]) && str[(*i)])
	{
		line = ft_add_line_after(line, str[(*i)]);
		if (!line)
			return (0);
		(*i)++;
	}
	if (!line || !ft_add_to_fstack_out(cmd, line))
	{
		printf("Minishell: syntax error\n");
		return (0);
	}
	free(line);
	return (1);
}


int	ft_add_file_in(t_cmd **cmd, int *i, char *str, char *line)
{
	while (is_redir(str[*i]) || is_blank(str[*i]))
		(*i)++;
	while (!is_blank(str[*i]) && str[(*i)])
	{
		line = ft_add_line_after(line, str[(*i)]);
		if (!line)
			return (0);
		(*i)++;
	}
	if (!line || !ft_add_to_fstack_in(cmd, line))
	{
		printf("Minishell: syntax error\n");
		return (0);
	}
	free(line);
	return (1);
}


t_file	*new_elem_file(t_cmd *cmd)
{
	t_file	*elem;

	(void)cmd;//to free after only
	elem = malloc(sizeof(t_file));
	if (!elem)
		//exit_custom(mini, NULL, AUTO);
		printf("Exist and Free mini\n");
	elem->type = 0;
	elem->name = NULL;
	return (elem);
}


void	add_files(t_file **file_lst, t_file *file)
{
	t_file	*current;

	if (!(*file_lst))
	{
		*file_lst = file;
		return ;
	}
	current = *file_lst;
	while (current->next)
		current = current->next;
	current->next = file;
	//cmd->prev = current;
}

int	check_redir(char *line, int i)
{
	int	k;
	int	j;

	k = 0;
	j = i;
	while (line[i] == '>' || line[i] == '<')
	{
		k++;
		i++;
	}
	if (k == 1 || k == 2)
	{
		if (k == 1)
			return (1);
		else if (k == 2 && line[j] == line[j + 1])
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	ft_redirec(char *line, int *i, char *str, t_cmd **tmp)
{
	t_file	*t;
	t = (*tmp)->file_out;
	t_file	*file_in_2;
	t_file	*file;
	t_mini *mini;

	file = NULL;
	mini = NULL;
	if (!check_redir(line, *i))
	{
		printf("Minishell: syntax error\n");
		(*tmp)->stop = 1;
		exit (0);
		return (0);
	}
	if (str)
	{
		ft_avs(*tmp, str);
		str = NULL;
	}
	ft_set_direct(line, i, *tmp);
	if (line[*i] == '<')
		ft_add_file_in(tmp, i, line, str);
	else if (line[*i] == '>')
		ft_add_file_out(tmp, i, line, str);
	file_in_2 = (*tmp)->file_in;
	t = (*tmp)->file_out;
	line = NULL;
	printf("DONE FT_REDIR \n\n");
	return (1);
}

int	quote_pass(char *line, int *i)
{
	if (line[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(line, i);
	return (1);
}

int str_blank(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_each_cmd_4(t_mini *mini, char *line, int *i, t_cmd **cmd)
{
	char		*buf;
	char		*line_after;

	line_after = NULL;
	printf("3. Inside each_cmd ^^ Orgine line is : %s\n", line);
	while (line[*i]/* && line[*i] != '|'*/)
	{
		(*cmd)->stop = 0;
		if (line[*i] == ' ')
		{
		//	printf("in ESPACE line_after = %s\n", line_after);
			skip_blank_2(line, i, *cmd, line_after);
			line_after = NULL;
		}
		if (line[*i] == '"')
		{
			line_after = ft_d2_quotes(line_after, i, line, *cmd, mini);
			ft_avs(*cmd, line_after);
			if ((*cmd)->stop == 1)
				return (0);
			 if (!quote_pass(line, i))
				break ;
			line_after = NULL;
		}
		else if (line[*i] == '\'')
		{
			line_after = ft_single_quote(line_after, i, line, *cmd);
			ft_avs(*cmd, line_after);
			if ((*cmd)->stop == 1)
				return (0);
			if (line[(*i) + 1] == '\0')
				break ;
			ft_pass_squote(line, i);
			line_after = NULL;
		}
		else if (line[*i] == '$' && !(line[(*i) + 1] == '?'))
		{
			line_after = dolar_name(line, i, line_after, *cmd);
			ft_avs(*cmd, dolar_2(line, i, line_after, mini->env));
			line_after = NULL;
		}
		else if (is_redir(line[*i]))
		{
			if (!ft_redirec(line, i, line_after, &*cmd))
				return (0);
		}
		else if (line[*i] == '|')
		{
			if (line_after)
				ft_avs(*cmd, line_after);
			break ;
		}
		else
		{
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if ((!line[*i] && line_after)/* || (line[*i + 1] == '|' && line_after)*/)
				ft_avs(*cmd, line_after);
			free(buf);
		}
	}
	return (1);
}
