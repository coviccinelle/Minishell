/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:45:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/08 15:48:10 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		while (p && p->next)
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