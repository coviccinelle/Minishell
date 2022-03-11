/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:46:48 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/11 12:18:23 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_each_cmd_4(t_mini *m, int *i, t_cmd **cmd, char ***env)
{
	t_param		p;

	ft_init_param(&p, env, i);
	while (m->line[p.i])
	{
		///----------------------------
		if (m->line[p.i] == ' ')
		{
			skip_blank_2(m->line, &p.i, *cmd, (*cmd)->la);
			(*cmd)->la = NULL;
			if (!m->line[p.i])
				break ;
		}
		else if (m->line[p.i] == '"')
		{
			if (m->line[p.i + 1] && (m->line[p.i + 1] == '\"'))
			{
				p.i += 2;
				break ;
			}
			(*cmd)->la = ft_d2_quotes(&p.i, *cmd, m, env);
			if (!(*cmd)->la)
				return (0);
			if (!ft_strcmp((*cmd)->la, "?"))
			{
				ft_avs(*cmd, ft_itoa(g_exit_value));
				break ;
			}
			avs_and_nul(*cmd, (*cmd)->la);
			if (!quote_pass_2(m->line, &p.i))
				break ;
			(*cmd)->la = NULL;
		}
		///----------------------------

		else if (m->line[p.i] == '\'')
		{
			if (m->line[p.i + 1] && (m->line[p.i + 1] == '\''))
			{
				p.i += 2;
				break ;
			}
			(*cmd)->la = ft_single_quote(&p.i, m->line, *cmd);
			if (!(*cmd)->la)
				return (0);
			avs_and_nul(*cmd, (*cmd)->la);
			if (m->line[p.i + 1] == '\0')
				break ;
			ft_pass_squote(m->line, &p.i);
			(*cmd)->la = NULL;
		}

		else if (m->line[p.i] == '$' && is_dollar(m->line[p.i + 1]))
		{
			p.va_2 = dolar_name(m->line, &p.i, (*cmd)->la, *cmd);
			(*cmd)->la = p.va_2;
			p.var = dolar_2(m->line, &p.i, (*cmd)->la, *env);
			if (*(*cmd)->la == '?')
				ft_avs(*cmd, ft_itoa(g_exit_value));
			avs_and_nul(*cmd, p.var);
			free(p.va_2);
			(*cmd)->la = NULL;
		}
		///----------------------------

		else if (is_redir(m->line[p.i]))
		{
			if (!ft_redirec(m->line, &p.i, (*cmd)->la, &*cmd))
				return (0);
			else
				p.i++;
		}

		else if (m->line[p.i] == '|')
		{
			avs_and_nul(*cmd, (*cmd)->la);
			break ;
		}
				///----------------------------
		else
		{
			p.buf = malloc(sizeof(char) * 2);
			ft_buf(m->line, &p.i, p.buf);
			(*cmd)->la = ft_add_line_after((*cmd)->la, p.buf[0]);
			if ((!m->line[p.i]))
				avs_and_nul(*cmd, (*cmd)->la);
			free(p.buf);
		}
	}
	(*i) = p.i;
	return (1);
}
