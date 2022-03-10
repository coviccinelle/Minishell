/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 22:00:13 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// more than 25 lines =>82 lignes
//if ret 0, ret 0 / quitte fonction ->free
//if ret 1, break
//if ret 2, continue / parsing ok

int	ft_each_cmd_4(t_mini *mini, int *i, t_cmd **cmd, char ***env)
{
	char		*buf;
	char		*va_2;
	char		*var;

	while (mini->line[*i])
	{
		if (mini->line[*i] == ' ')
		{
			skip_blank_2(mini->line, i, *cmd, (*cmd)->la);
			(*cmd)->la = NULL;
			if (!mini->line[*i])
				break ;
		}
		else if (mini->line[*i] == '"')
		{
			if (mini->line[*i + 1] && (mini->line[*i + 1] == '\"'))
			{
				(*i) += 2;
				break ;
			}
			(*cmd)->la = ft_d2_quotes(i, *cmd, mini, env);
			if (!(*cmd)->la)
				return (0);
			if (!ft_strcmp((*cmd)->la, "?"))
			{
				ft_avs(*cmd, ft_itoa(g_exit_value));
				break ;
			}
			avs_and_nul(*cmd, (*cmd)->la);
			if (!quote_pass_2(mini->line, i))
				break ;
			(*cmd)->la = NULL;
		}
		else if (mini->line[*i] == '\'')
		{
			if (mini->line[*i + 1] && (mini->line[*i + 1] == '\''))
			{
				(*i) += 2;
				break ;
			}
			(*cmd)->la = ft_single_quote(i, mini->line, *cmd);
			if (!(*cmd)->la)
				return (0);
			avs_and_nul(*cmd, (*cmd)->la);
			if (mini->line[(*i) + 1] == '\0')
				break ;
			ft_pass_squote(mini->line, i);
			(*cmd)->la = NULL;
		}
		else if (mini->line[*i] == '$' && mini->line[*i + 1] && mini->line[*i + 1] != ' ')
		{
			va_2 = dolar_name(mini->line, i, (*cmd)->la, *cmd);
			(*cmd)->la = va_2;
			var = dolar_2(mini->line, i, (*cmd)->la, *env);
			if (*(*cmd)->la == '?')
				ft_avs(*cmd, ft_itoa(g_exit_value));
			avs_and_nul(*cmd, var);
			free(va_2);
			(*cmd)->la = NULL;
		}
		else if (is_redir(mini->line[*i]))
		{
			if (!ft_redirec(mini->line, i, (*cmd)->la, &*cmd))
				return (0);
			else
				(*i)++;
		}
		else if (mini->line[*i] == '|')
		{
			avs_and_nul(*cmd, (*cmd)->la);
			break ;
		}
		else
		{
			buf = malloc(sizeof(char) * 2);
			ft_buf(mini->line, i, buf);
			(*cmd)->la = ft_add_line_after((*cmd)->la, buf[0]);
			if ((!mini->line[*i]))
				avs_and_nul(*cmd, (*cmd)->la);
			free(buf);
		}
	}
	return (1);
}
