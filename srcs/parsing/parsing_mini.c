/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:46:48 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/14 18:01:43 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	first_if(t_cmd **cmd, t_mini *m, t_param *p)
{
	if (m->line[p->i] == ' ')
	{
		skip_blank_2(m->line, &p->i, *cmd, (*cmd)->la);
		(*cmd)->la = NULL;
		if (!m->line[p->i])
			return (-1);
		return (1);
	}
	else if (m->line[p->i] == '"')
	{
		if (m->line[p->i + 1] && (m->line[p->i + 1] == '\"'))
			return (p->i += 2, -1);
		(*cmd)->la = ft_d2_quotes(&p->i, *cmd, m, p->env);
		if (!ft_strcmp((*cmd)->la, ""))
		{
			free((*cmd)->la);
			return (0);
		}
		if (!ft_strcmp((*cmd)->la, "?"))
			return (ft_avs(*cmd, ft_itoa(g_exit_value)), -1);
		avs_and_nul(*cmd, (*cmd)->la);
		if (!quote_pass_2(m->line, &p->i))
			return (-1);
		(*cmd)->la = NULL;
		return (1);
	}
	return (2);
}
	// return (-1) = break;
	// return (1) on deja passer dans un if
	// return (2) il faut passer dans les autres if

int	second_if(t_cmd **cmd, t_mini *m, t_param *p)
{
	if (m->line[p->i] == '\'')
	{
		if (m->line[p->i + 1] && (m->line[p->i + 1] == '\''))
			return (p->i += 2, -1);
		(*cmd)->la = ft_single_quote(&p->i, m->line, *cmd);
		if (!ft_strcmp((*cmd)->la, ""))
			return (0);
		avs_and_nul(*cmd, (*cmd)->la);
		if (m->line[p->i + 1] == '\0')
			return (-1);
		ft_pass_squote(m->line, &p->i);
		(*cmd)->la = NULL;
		return (1);
	}
	else if (m->line[p->i] == '$' && is_dollar(m->line[p->i + 1]))
	{
		p->va_2 = dolar_name(m->line, &p->i, (*cmd)->la, *cmd);
		(*cmd)->la = p->va_2;
		p->var = dolar_2(m->line, &p->i, (*cmd)->la, *(p->env));
		if (*(*cmd)->la == '?')
			ft_avs(*cmd, ft_itoa(g_exit_value));
		avs_and_nul_2(*cmd, p->var, p->va_2);
		return (1);
	}
	return (2);
}
	// return (-1) = break;
	// return (1) on deja passer dans un if
	// return (0) il faut return (0);
	// return (2) il faut passer dans les autres if

int	third_if(t_cmd **cmd, t_mini *m, t_param *p)
{
	if (is_redir(m->line[p->i]))
	{
		if (!ft_redirec(m->line, &p->i, (*cmd)->la, &*cmd))
			return (0);
		else
			return (p->i++, 1);
	}
	else if (m->line[p->i] == '|')
		return (avs_and_nul(*cmd, (*cmd)->la), -1);
	else
	{
		p->buf = malloc(sizeof(char) * 2);
		ft_buf(m->line, &p->i, p->buf);
		(*cmd)->la = ft_add_line_after((*cmd)->la, p->buf[0]);
		if ((!m->line[p->i]))
			avs_and_nul(*cmd, (*cmd)->la);
		free(p->buf);
		return (1);
	}
	return (1);
}
	// return (-1) = break;
	// return (1) on deja passer dans un if
	// return (0) il faut return (0);

int	ft_each_cmd_4(t_mini *m, int *i, t_cmd **cmd, char ***env)
{
	t_param		p;

	ft_init_param(&p, env, i);
	while (m->line[p.i])
	{
		p.ret1 = first_if(cmd, m, &p);
		if (p.ret1 == 2)
		{
			p.ret2 = second_if(cmd, m, &p);
			if (p.ret2 == 0)
				return (0);
			else if (p.ret2 == 2)
			{
				p.ret3 = third_if(cmd, m, &p);
				if (p.ret3 == 0)
					return (0);
				else if (p.ret3 == -1)
					break ;
			}
		}
		if (p.ret1 == -1 || p.ret2 == -1)
			break ;
		if (p.ret1 == 0)
			return (0);
	}
	return ((*i) = p.i, 1);
}
