/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirrection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:53:50 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/09 23:52:02 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
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

void	avs_and_nul(t_cmd *cmd, char *str)
{
	if (str)
	{
		ft_avs(cmd, str);
	//	free(str);
	}
}

int	ft_redirec(char *line, int *i, char *str, t_cmd **tmp)
{
//	t_file	*t;
//	t_file	*file_in_2;
//	t_file	*file;
//	t_mini	*mini;

//	t = (*tmp)->file_out;
//	file = NULL;
//	mini = NULL;
	if (!check_redir(line, *i))
	{
		printf("Minishell: syntax error\n");
		return (0);
	}
	avs_and_nul(*tmp, str);
	ft_set_direct(line, i, *tmp);
	if (line[*i] == '<')
		ft_add_file_in(tmp, i, line, str);
	else if (line[*i] == '>')
		ft_add_file_out(tmp, i, line, str);
//	file_in_2 = (*tmp)->file_in;
//	t = (*tmp)->file_out;

	line = NULL;
	return (1);
}
