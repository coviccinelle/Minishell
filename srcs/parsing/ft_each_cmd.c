/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_each_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:26:39 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/10 00:00:56 by thi-phng         ###   ########.fr       */
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
int	ft_each_cmd_4(t_mini *mini, char *line, int *i, t_cmd **cmd, char ***env)
{
	char		*buf;
	char		*line_after;

	line_after = NULL;
	while (line[*i])
	{
		if (line[*i] == ' ')
		{
			skip_blank_2(line, i, *cmd, line_after);
			line_after = NULL;
			if (!line[*i])
				break ;
		}
		else if (line[*i] == '"')
		{
			if (line[*i + 1] && (line[*i + 1] == '\"'))
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
			//	free(line_after);
				break ;
			}
			avs_and_nul(*cmd, line_after);
			
			if (!quote_pass_2(line, i))
			{
			//	free(line_after);
				break ;
			}
				
			line_after = NULL;
		}
		else if (line[*i] == '\'')
		{
			if (line[*i + 1] && (line[*i + 1] == '\''))
			{
				(*i) += 2;
				break ;
			}
			line_after = ft_single_quote(line_after, i, line, *cmd);
			if (!line_after)
				return (0);
			avs_and_nul(*cmd, line_after);
			if (line[(*i) + 1] == '\0')
				break ;
			ft_pass_squote(line, i);
			line_after = NULL;
		}
		else if (line[*i] == '$'/* && !(line[(*i) + 1] == '?')*/)
		{
			line_after = dolar_name(line, i, line_after, *cmd);
			char *var = dolar_2(line, i, line_after, *env);
			if (*line_after == '?')
				ft_avs(*cmd, ft_itoa(g_exit_value));
		//	avs_and_nul(*cmd, dolar_2(line, i, line_after, *env));
			avs_and_nul(*cmd, var);
			//free(var);
			line_after = NULL;
		}
		else if (is_redir(line[*i]))
		{
			if (!ft_redirec(line, i, line_after, &*cmd))
			{
			//	free(line_after);
				return (0);
			}
			else
				(*i)++;
		}
		else if (line[*i] == '|')
		{
			avs_and_nul(*cmd, line_after);
			//free(line_after);
			break ;
		}
		else
		{
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if ((!line[*i]))
				avs_and_nul(*cmd, line_after);
			free(buf);
		}
	//	free(line_after);
	}
	
	return (1);
}
