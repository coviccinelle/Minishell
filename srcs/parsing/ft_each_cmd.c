/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 20:25:27 by thi-phng         ###   ########.fr       */
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
	char		*line_after;
	char		*va_2;
	char		*var;

	line_after = NULL;
	while (mini->line[*i])
	{
		if (mini->line[*i] == ' ')
		{
			skip_blank_2(mini->line, i, *cmd, line_after);
			line_after = NULL;
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
			line_after = ft_d2_quotes(line_after, i, *cmd, mini, env);
			if (!line_after)
				return (0);
			if (!ft_strcmp(line_after, "?"))
			{
				ft_avs(*cmd, ft_itoa(g_exit_value));
				break ;
			}
			avs_and_nul(*cmd, line_after);
			if (!quote_pass_2(mini->line, i))
				break ;
			line_after = NULL;
		}
		else if (mini->line[*i] == '\'')
		{
			if (mini->line[*i + 1] && (mini->line[*i + 1] == '\''))
			{
				(*i) += 2;
				break ;
			}
			line_after = ft_single_quote(line_after, i, mini->line, *cmd);
			if (!line_after)
				return (0);
			avs_and_nul(*cmd, line_after);
			if (mini->line[(*i) + 1] == '\0')
				break ;
			ft_pass_squote(mini->line, i);
			line_after = NULL;
		}
		else if (mini->line[*i] == '$')
		{
			va_2 = dolar_name(mini->line, i, line_after, *cmd);
			line_after = va_2;
			var = dolar_2(mini->line, i, line_after, *env);
			if (*line_after == '?')
				ft_avs(*cmd, ft_itoa(g_exit_value));
			avs_and_nul(*cmd, var);
			free(va_2);
			line_after = NULL;
		}
		else if (is_redir(mini->line[*i]))
		{
			if (!ft_redirec(mini->line, i, line_after, &*cmd))
				return (0);
			else
				(*i)++;
		}
		else if (mini->line[*i] == '|')
		{
			avs_and_nul(*cmd, line_after);
			break ;
		}
		else
		{
			buf = malloc(sizeof(char) * 2);
			ft_buf(mini->line, i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if ((!mini->line[*i]))
				avs_and_nul(*cmd, line_after);
			free(buf);
		}
	}
	return (1);
}
